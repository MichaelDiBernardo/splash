#include <assert.h>
#include "Engine.h"
#include "os.h"
#include "ChaserAgent.h"
#include "Config.h"
#include "DinoState.h"
#include "EngineInput.h"
#include "Level.h"
#include "PropSpec.h"
#include "Timer.h"
#include <iostream>
using namespace std;

Engine::Engine() {
  currentLevel_ = new Level(1);
  init();
}

Engine::Engine(int level) {
  currentLevel_ = new Level(level);
  init();
}

Engine::~Engine() {
  for (int i = 0; i < currentLevel_->getNumNPCs(); ++i) delete agents_[i];
  delete levelTimer_;
  delete powerupTimer_;
  delete [] agents_;
  delete currentLevel_;
}

void Engine::init() {
  agents_ = new ChaserAgent*[currentLevel_->getNumNPCs()];
  
  for (int i = 0; i < currentLevel_->getNumNPCs(); ++i) {
    agents_[i] = new ChaserAgent(*(currentLevel_->getPCState()), 
                                currentLevel_->getNPCState(i));
  }

  levelTimer_ = new Timer();
  numDotsLeft_ = currentLevel_->getDots()->size();
  currentEffect_ = PE_NONE;
  powerupTimer_ = new Timer();
  isModelFrozen_ = false;
  isPlayerInvincible_ = false;
  firstTick_ = true;
  win_ = NULL;
  gameOver_ = false;
}

EngineState Engine::evolve(const EngineInput &inputs) {
  // Check if we're 'live'.
  if (isModelFrozen_) return ES_RUNNING;
  if (firstTick_) {
    levelTimer_->start();
    firstTick_ = false;
  }

  // Potentially expire any effective powerups.
  if (currentEffect_ != PE_NONE &&
      powerupTimer_->getTimeInMicroseconds() >= Config::POWERUP_DURATION_IN_MICROSECONDS) {
    currentEffect_ = PE_NONE;
    powerupTimer_->pause();
  }

  // Exert inputs on player character.
  if (inputs.playerMovingForward())
    currentLevel_->getPCState()->setMovingForward();
  else if (inputs.playerMovingBackward())
    currentLevel_->getPCState()->setMovingBackward();
  else
    currentLevel_->getPCState()->stopMoving();

  if (inputs.playerTurningLeft())
    currentLevel_->getPCState()->setTurningLeft();
  else if (inputs.playerTurningRight())
    currentLevel_->getPCState()->setTurningRight();
  else
    currentLevel_->getPCState()->stopTurning();

  // Move the PC according to the given inputs.
  currentLevel_->getPCState()->evolve(currentEffect_);
  // PC may have fallen off of the board: If so, constrain PC back into
  // the level.
  currentLevel_->getPCState()->clipPosition(0, 0, currentLevel_->getWidth(), currentLevel_->getHeight());

  for (int i = 0; i < currentLevel_->getNumNPCs(); ++i) {
    agents_[i]->control();
    currentLevel_->getNPCState(i)->evolve(currentEffect_);
    currentLevel_->getNPCState(i)->clipPosition(0, 0, currentLevel_->getWidth(), currentLevel_->getHeight());
  }

  for (list<PropSpec*>::iterator it = currentLevel_->getProps()->begin();
       it != currentLevel_->getProps()->end();
       ++it) {
    PropSpec* p = *it;

    // If the PC has staggered into any props, boot it out of there.
    if (p->contains(currentLevel_->getPCState()->getOrientation())) {
      Orientation clipped = p->clip(currentLevel_->getPCState()->getOrientation());
      currentLevel_->getPCState()->setOrientation(clipped);
    }

    // Same for NPCs.
    for (int i = 0; i < currentLevel_->getNumNPCs(); ++i) {
      if (p->contains(currentLevel_->getNPCState(i)->getOrientation())) {
        Orientation clipped = p->clip(currentLevel_->getNPCState(i)->getOrientation());
        currentLevel_->getNPCState(i)->setOrientation(clipped);
      }
    }
  }
  
  // Eat any dots that the player may have run into.
  if (!gameOver_) {
    for (list<PropSpec*>::iterator d_it = currentLevel_->getDots()->begin();
         d_it != currentLevel_->getDots()->end();
         ++d_it) {
      PropSpec* d = *d_it;
      if (d->isActive() && d->contains(currentLevel_->getPCState()->getOrientation())) {
        d->setActive(false);
        numDotsLeft_--;
      }
    }
  }

  // Check for game over (in a good way).
  if (numDotsLeft_ == 0 && !gameOver_) {
    handleWin();
    setInvincible(true);
    gameOver_ = true;
  }

  for (list<PropSpec*>::iterator pup_it = currentLevel_->getPowerups()->begin();
       pup_it != currentLevel_->getPowerups()->end();
       ++pup_it) {
    PropSpec* pu = *pup_it;
    if (pu->isActive() && pu->contains(currentLevel_->getPCState()->getOrientation())) {
      // This is hacky, and indicates need for a map or something, but we leave
      // it for now since there are only a few powerup types. 
      pu->setActive(false);
      if (pu->getType() == FEAR_POWERUP_PROP) {
        currentEffect_ = PE_FEAR;
      }
      else if (pu->getType() == SPEED_POWERUP_PROP) {
        currentEffect_ = PE_SPEED;
      }
      else if (pu->getType() == FREEZE_POWERUP_PROP) {
        currentEffect_ = PE_FREEZE;
      }
      else {
        assert(false);
      }

      powerupTimer_->reset();
      if (!powerupTimer_->running())
        powerupTimer_->start();
    }
  }

  // Bump all the dinos together.
  for (int i = 0; i < currentLevel_->getNumNPCs(); ++i) {
    if (!isPlayerInvincible_ && currentLevel_->getNPCState(i)->isHittingOtherDino(*currentLevel_->getPCState())) {
      setInvincible(true);
      levelTimer_->pause();
      gameOver_ = true;
    }

    currentLevel_->getNPCState(i)->crashWithDino(currentLevel_->getPCState());

    for (int j = 0; j < currentLevel_->getNumNPCs(); ++j) {
      if (i != j)
        currentLevel_->getNPCState(i)->crashWithDino(currentLevel_->getNPCState(j));
    }
  }
  return getEngineState();
}

EngineState Engine::getEngineState() const {
  if (!gameOver_) return ES_RUNNING;
  else if (numDotsLeft_ == 0) return ES_WON;
  else return ES_LOST;
}

void Engine::toggleInvincible() {
  isPlayerInvincible_ = !isPlayerInvincible_;
  if (isPlayerInvincible_) cout << "Invincibility ON" << endl;
  else cout << "Invincibility OFF" << endl;
}

void Engine::setInvincible(bool to) {
  isPlayerInvincible_ = to;
}

void Engine::toggleFrozen() {
  if (isModelFrozen_) levelTimer_->start();
  else levelTimer_->pause();
  isModelFrozen_ = !isModelFrozen_;
}

bool Engine::isFrozen() const {
  return isModelFrozen_;
}

const Level& Engine::getCurrentLevel() const {
  return *currentLevel_;
}

int Engine::getNumDotsLeft() const {
  return numDotsLeft_;
}

long Engine::getMillisecondsSpentOnLevel() const {
  return levelTimer_->getTimeInMilliseconds();
}

PowerupEffect Engine::getCurrentPowerup() const {
  return currentEffect_;
}

long Engine::getTimeLeftInPowerup() const {
  return Config::POWERUP_DURATION_IN_MICROSECONDS - 
         powerupTimer_->getTimeInMicroseconds();
}

WinRecord* Engine::getWinInfo() const {
  assert(win_ != NULL);
  return win_;
}

void Engine::handleWin() {
  // Stop timing!
  levelTimer_->pause();

  // Generate win record.
  win_ = new WinRecord;
  win_->newTime = levelTimer_->getTimeInMilliseconds();
  win_->par = currentLevel_->getPar();
  win_->level = currentLevel_->getLevelNumber();
  if (currentLevel_->getLevelNumber() == Level::getNumLevelsUnlocked() && 
      win_->newTime <= currentLevel_->getPar() * 1000) {
    win_->unlockedNextLevel = true;
  } else {
    win_->unlockedNextLevel = false;
  } 

  for (vector<long>::const_iterator it = currentLevel_->getRecordTimes().begin();
       it != currentLevel_->getRecordTimes().end();
       ++it) {
    win_->oldTimes.push_back(*it);
  }
  // Now update data.
  currentLevel_->handleWin(levelTimer_->getTimeInMilliseconds());
}

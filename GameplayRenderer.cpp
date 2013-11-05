// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class GameplayRenderer and related constructs.
#include <iostream>
using std::cout; using std::cerr; using std::endl;
#include "GameplayRenderer.h"
#include "Config.h"
#include "ColorSpec.h"
#include "Engine.h"
#include "EngineInput.h"
#include "Scene.h"
#include "Timer.h"

GameplayRenderer::GameplayRenderer(int level) 
  : engine_(new Engine(level)), 
    inputs_(new EngineInput()), 
    startupTimer_(new Timer()), 
    scene_(new Scene(*engine_, *startupTimer_)) { 
}

GameplayRenderer::~GameplayRenderer() {
  delete scene_;
  delete inputs_;
  delete engine_;
  delete startupTimer_;
}

void GameplayRenderer::init() {
  glClearColor (Config::SKY_COLOR->r(), Config::SKY_COLOR->g(), Config::SKY_COLOR->b(), Config::SKY_COLOR->a());
  glShadeModel (GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  startupTimer_->start();
  disable();
}

NextAction GameplayRenderer::render() {
  EngineState state = ES_RUNNING;

  if (!startupTimer_->running()) {
    state = engine_->evolve(*inputs_);
  } else if (startupTimer_->getTimeInMilliseconds() > Config::COUNTDOWN_LENGTH) {
    enable();
    startupTimer_->pause();
  }
  scene_->render();

  if (state == ES_RUNNING) {
    return RA_REDISPLAY;
  } else if (state == ES_WON) {
    return RA_GAME_WON_TO_FADE;
  } else {
    return RA_GAME_LOST_TO_FADE;
  }
}

void GameplayRenderer::reshape(int w, int h) {
  gluPerspective(70.0, (GLfloat) w/h, 0.01, 100.0);
}

void GameplayRenderer::onKeyDown(unsigned char key, int x, int y) {
  if (key == 'X' || key== 'x')
    scene_->zoomIn();
  else if (key == 'Z' || key == 'z')
    scene_->zoomOut();
  else if (key == 'S' || key == 's')
    scene_->liftCam();
  else if (key == 'A' || key == 'a')
    scene_->dropCam();
  else if (key == ' ' && engine_->getEngineState() == ES_RUNNING) {
    engine_->toggleFrozen();
  }
  else if (key == '+' || key == '=') {
    double newFR = Config::changeFrameRate(-5);
    cout << "Game speed up (" << newFR << " FPS)" << endl;
  }
  else if (key == '-' || key == '_') {
    double newFR = Config::changeFrameRate(5);
    cout << "Game speed down (" << newFR << " FPS)" << endl;
  }
}

void GameplayRenderer::onSpecialKeyDown(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    if (!inputs_->playerMovingBackward())
      inputs_->setPlayerMovingForward(true);
  }
  else if (key == GLUT_KEY_DOWN) {
    if (!inputs_->playerMovingForward())
      inputs_->setPlayerMovingBackward(true);
  }
  else if (key == GLUT_KEY_LEFT) {
    if (!inputs_->playerTurningRight())
      inputs_->setPlayerTurningLeft(true);
  }
  else if (key == GLUT_KEY_RIGHT) {
    if (!inputs_->playerTurningLeft())
      inputs_->setPlayerTurningRight(true);
  }
}

void GameplayRenderer::onSpecialKeyUp(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    inputs_->setPlayerMovingForward(false);
  }
  else if (key == GLUT_KEY_DOWN) {
    inputs_->setPlayerMovingBackward(false);
  }
  else if (key == GLUT_KEY_LEFT) {
    inputs_->setPlayerTurningLeft(false);
  }
  else if (key == GLUT_KEY_RIGHT) {
    inputs_->setPlayerTurningRight(false);
  }
}

bool GameplayRenderer::shouldKeysRepeat() const {
  return false;
}

WinRecord* GameplayRenderer::getWinInfo() const {
  return engine_->getWinInfo();
}

// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class HUDNode and related constructs.
#include "HUDNode.h"
#include <assert.h>
#include <math.h>
#include "os.h"
#include "ColorSpec.h"
#include "Config.h"
#include "Engine.h"
#include "Format.h"
#include "Level.h"
#include "Timer.h"
#include "Utils2D.h"
#define PASS ;

HUDNode::HUDNode(const string& id, const Engine& model, const Timer& startupTimer) 
  : SceneNode(id), 
    model_(model), 
    parString_(Format::secondsToTicker(model_.getCurrentLevel().getPar())),
    startupTimer_(startupTimer) {
}

HUDNode::~HUDNode() {
}

void drawDotCount(const string& dotString) {
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(2600, 2850, 0);
  glColor3f(0, 0, 0);
  Utils2D::drawShinyBall(75);

  glTranslatef(150, -55, 0);
  glColor3f(1, 1, 1);
  Utils2D::drawString(dotString);
  glPopMatrix();
}

void drawElapsedTime(const string& timerString) {
  glPushMatrix();
  glLoadIdentity();

  glTranslatef(1300, 2800, 0);
  glColor3f(1, 1, 1);
  Utils2D::drawString(timerString);

  glPopMatrix();
}

void drawParTime(const string& parString) {
  glPushMatrix();
  glLoadIdentity();

  glTranslatef(2400, 200, 0);
  glColor3f(1, 1, 0);
  Utils2D::drawString(parString);

  glPopMatrix();
}


void drawElapsedPowerupTimeBar(PowerupEffect effect, long timeLeft) {
  const float kBarHeight = 100.0f;
  const float kBarWidth = 800.0f;

  glPushMatrix();
  glLoadIdentity();

  glTranslatef(100, 2800, 0);
  glColor3f(0, 0, 0);
  glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, kBarHeight, 0);
    glVertex3f(kBarWidth, kBarHeight, 0);
    glVertex3f(kBarWidth, 0, 0);
  glEnd();

  if (effect != PE_NONE) {
    switch (effect) {
      case PE_SPEED:
        Config::SPEED_POWERUP_COLOR->set(); break;
      case PE_FEAR:
        Config::FEAR_POWERUP_COLOR->set(); break;
      case PE_FREEZE:
        Config::FREEZE_POWERUP_COLOR->set(); break;
      default:
        assert(false);
    }
    
    float width = (static_cast<float>(timeLeft) / Config::POWERUP_DURATION_IN_MICROSECONDS) * kBarWidth;
    glBegin(GL_QUADS);
      glVertex3f(0, 0, 0);
      glVertex3f(0, kBarHeight, 0);
      glVertex3f(width, kBarHeight, 0);
      glVertex3f(width, 0, 0);
    glEnd();
  }

  glPopMatrix();
}

void drawPauseScreen() {
  glColor4f(0, 0, 0, 0.5);
  glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, Config::MAX_2D_COORD, 0);
    glVertex3f(Config::MAX_2D_COORD, Config::MAX_2D_COORD, 0);
    glVertex3f(Config::MAX_2D_COORD, 0, 0);
  glEnd();
}

void drawCountdown(long elapsed) {
  elapsed /= 1000;
  glColor3f(1, 1, 0);

  if (elapsed < 1) {
    PASS
  } else if (elapsed < 3) {
    Utils2D::drawString("3", 1450, 800);
  } else if (elapsed < 4) {
    Utils2D::drawString("2", 1450, 800);
  } else if (elapsed < 5) {
    Utils2D::drawString("1", 1450, 800);
  } else if (elapsed < 6) {
    Utils2D::drawString("GO!", 1400, 800);
  }
}

void drawEndgameMessage(EngineState state) {
  if (state != ES_WON && state != ES_LOST) return;

  string message;
  if (state == ES_WON) {
    message = "STAGE CLEAR!";
  } else {
    message = "  YOU LOST! ";
  }

  glColor3f(1, 1, 0);
  Utils2D::drawString(message, 1000, 800);
}

void HUDNode::render() {
  glPushMatrix();

  // Switch to 2d orthographic projection and save old projection matrix.
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  // We have to make this huge because glStrokeCharacter draws characters that
  // are a fixed number of units in size (120-odd tall and about half that in
  // width.) This makes more sense to me than scaling everywhere.
  gluOrtho2D(0.0, Config::MAX_2D_COORD, 0.0, Config::MAX_2D_COORD);
  
  // Save all settings, because we're about to mess with them.
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  
  // Disable depth test so that our scribblings will actually show up, and
  // enable settings that will antialias our fonts.
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(2.0);

  glMatrixMode(GL_MODELVIEW);
      
  if (startupTimer_.running()) {
    drawCountdown(startupTimer_.getTimeInMilliseconds());
  }
  drawEndgameMessage(model_.getEngineState());
  drawDotCount(Format::intToString(model_.getNumDotsLeft()));
  drawElapsedTime(Format::millisecondsToTicker(model_.getMillisecondsSpentOnLevel()));
  drawParTime(parString_);
  drawElapsedPowerupTimeBar(model_.getCurrentPowerup(), model_.getTimeLeftInPowerup());

  // Grey out screen if frozen.
  if (model_.isFrozen()) {
    drawPauseScreen();
  }

  glMatrixMode(GL_PROJECTION);

  // Restore attributes.
  glPopAttrib();
  
  // Restore the previous projection.
  glPopMatrix();

  // Return to model/view mode and restore the old model/view matrix.
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

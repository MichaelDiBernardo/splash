// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class MenuRenderer and related constructs.
#include "MenuRenderer.h"
#include <math.h>
#include "os.h"
#include "Config.h"
#include "Format.h"
#include "Level.h"
#include "Timer.h"
#include "Utils2D.h"

MenuRenderer::MenuRenderer() 
  : TexturedScreenRenderer(Config::MENU_IMAGE),
    currentSelectedLevel_(0), 
    numLevelsUnlocked_(Level::getNumLevelsUnlocked()),
    picked_(false) {
  for (int i = 1; i <= Config::NUM_LEVELS; ++i) {
    levels_.push_back(new Level(i));
  }
}

MenuRenderer::~MenuRenderer() {
  STLDeleteContainerPointers(levels_.begin(), levels_.end());
}

NextAction MenuRenderer::renderOverBackground() {
  glPushMatrix();

  const double kLeftColumn = 900.0;
  const double kMidColumn = 1500.0;

  glColor3f(1, 1, 0);
  glLineWidth(2.0);
  Utils2D::drawString("Level:", kLeftColumn, 2000.0);
  Utils2D::drawString("Par:", kLeftColumn, 1800.0);
  Utils2D::drawString("Records:", kLeftColumn, 1400.0);
  
  glLineWidth(1.0);
  glColor3f(1, 1, 1);
  Utils2D::drawString(Format::intToString(currentSelectedLevel_ + 1), kMidColumn, 2000.0);

  double recPos = 1400.0;
  const string kHuh = "??:??:??";
  Utils2D::drawString(
      locked() ? kHuh : Format::secondsToTicker(levels_[currentSelectedLevel_]->getPar()), 
      kMidColumn, 1800.0);
  
  const vector<long>& records = levels_[currentSelectedLevel_]->getRecordTimes();

  for (vector<long>::const_iterator it = records.begin();
       it != records.end();
       ++it) {
    Utils2D::drawString(
        locked() ? kHuh : Format::millisecondsToTicker(*it), 
        kMidColumn, recPos);
    recPos -= 200.0;
  }

  glPopMatrix();
  
  if (picked_) {
    return RA_MENU_TO_FADE;
  } else {
    return RA_REDISPLAY;
  }
}

void MenuRenderer::onKeyDown(unsigned char key, int x, int y) {
  if ( (key == ' ' || static_cast<int>(key) == 13) && !locked()) {
    picked_ = true;
    disable();
  }
}

void MenuRenderer::onSpecialKeyDown(int key, int x, int y) {
  if (key == GLUT_KEY_UP || key == GLUT_KEY_RIGHT) {
    currentSelectedLevel_ = (currentSelectedLevel_ + 1) % Config::NUM_LEVELS;
  }
  else if (key == GLUT_KEY_DOWN || key == GLUT_KEY_LEFT) {
    currentSelectedLevel_--;
    if (currentSelectedLevel_ < 0) currentSelectedLevel_ = Config::NUM_LEVELS - 1;
  }
}

bool MenuRenderer::shouldKeysRepeat() const {
  return true;
}

int MenuRenderer::levelPicked() const {
  return (currentSelectedLevel_ + 1);
}

bool MenuRenderer::locked() const {
  return ( (currentSelectedLevel_ + 1) > numLevelsUnlocked_);
}

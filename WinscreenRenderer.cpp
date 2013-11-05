// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class WinscreenRenderer and related constructs.
#include "WinscreenRenderer.h"
#include "os.h"
#include "Config.h"
#include "Engine.h"
#include "Format.h"
#include "Utils2D.h"

WinscreenRenderer::WinscreenRenderer(WinRecord* win) : win_(win), switch_(false) {
}

WinscreenRenderer::~WinscreenRenderer() {
  delete win_;
}

void WinscreenRenderer::init() {
  glClearColor(0, 0, 0, 0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH_TEST);
}

NextAction WinscreenRenderer::render() {
  const double kLeftColumn = 900.0;
  const double kMidColumn = 1700.0;
  
  glColor3f(0, 0, 1);
  glLineWidth(3.0);
  Utils2D::drawString("LEVEL CLEAR!", kLeftColumn, 2400.0);

  glLineWidth(2.0);

  if (win_->unlockedNextLevel && win_->level < Config::NUM_LEVELS) {
    glColor3f(0.5, 0, 0);
    glPushMatrix();
    Utils2D::drawString("YOU UNLOCKED LEVEL " + Format::intToString(win_->level + 1), 
                        700.0, 100.0);
    glPopMatrix();
  }

  glColor3f(1, 1, 0);
  Utils2D::drawString("Level:", kLeftColumn, 2000.0);
  Utils2D::drawString("Par:", kLeftColumn, 1800.0);
  Utils2D::drawString("Your Time:", kLeftColumn, 1600.0);
  Utils2D::drawString("Records:", kLeftColumn, 1200.0);
  
  glLineWidth(1.0);
  glColor3f(1, 1, 1);
  Utils2D::drawString(Format::intToString(win_->level), kMidColumn, 2000.0);
  Utils2D::drawString(Format::secondsToTicker(win_->par), kMidColumn, 1800.0); 
  Utils2D::drawString(Format::millisecondsToTicker(win_->newTime), kMidColumn, 1600.0); 

  int newTimeIndex;
  for (newTimeIndex = 0; newTimeIndex < Config::NUM_RECORD_TIMES; ++newTimeIndex) {
    if (win_->newTime < win_->oldTimes[newTimeIndex]) break;
  }

  int ind = 0;
  double recPos = 1200.0;
  for (int i = 0; i < Config::NUM_RECORD_TIMES; ++i) {
    if (i == newTimeIndex) {
      glColor3f(0, 1, 0);
      Utils2D::drawString(
          Format::millisecondsToTicker(win_->newTime),
          kMidColumn, recPos);
      glColor3f(1, 1, 1);
    } else {
      Utils2D::drawString(
          Format::millisecondsToTicker(win_->oldTimes[ind]),
          kMidColumn, recPos);
      ++ind;
    }
    recPos -= 200.0;
  }

  if (switch_)
    return RA_WINSCREEN_TO_FADE;
  else 
    return RA_REDISPLAY;
}

void WinscreenRenderer::reshape(int newWidth, int newHeight) {
  gluOrtho2D(0.0, Config::MAX_2D_COORD, 0.0, Config::MAX_2D_COORD);
}

void WinscreenRenderer::onKeyDown(unsigned char key, int x, int y) {
  if (key == ' ' || static_cast<int>(key) == 13) switch_ = true;
}

bool WinscreenRenderer::shouldKeysRepeat() const {
  return false;
}

bool WinscreenRenderer::showEndScreen() const {
  if (win_->level == Config::NUM_LEVELS) return true;
  else return false;
}

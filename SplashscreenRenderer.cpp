// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class SplashscreenRenderer and related constructs.
#include "SplashscreenRenderer.h"
#include "ColorSpec.h"
#include "Config.h"
#include "Timer.h"
#include "Utils2D.h"
#include "os.h"

static const long kMillisecondsToWait = 2 * 1000;

SplashscreenRenderer::SplashscreenRenderer() 
  : TexturedScreenRenderer(Config::SPLASHSCREEN_IMAGE), pauser_(new Timer()), switch_(false) {
  disable();
}

SplashscreenRenderer::~SplashscreenRenderer() {
  delete pauser_;
}

NextAction SplashscreenRenderer::renderOverBackground() {
  glPushMatrix();

  if (!pauser_->running()) pauser_->start();

  if (pauser_->getTimeInMilliseconds() > kMillisecondsToWait) {
    glTranslatef(1000, 1000, 0);
    Utils2D::drawString("Press any key.");
    enable();
  }

  glPopMatrix();

  if (switch_) {
    return RA_TITLE_TO_FADE;
  } else {
    return RA_REDISPLAY;
  }

}

void SplashscreenRenderer::onKeyDown(unsigned char key, int x, int y) {
  switch_ = true;
}

bool SplashscreenRenderer::shouldKeysRepeat() const {
  return false;
}

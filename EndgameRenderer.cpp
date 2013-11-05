// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class EndgameRenderer and related constructs.
#include "EndgameRenderer.h"
#include "Config.h"

EndgameRenderer::EndgameRenderer() 
  : TexturedScreenRenderer(Config::ENDGAME_IMAGE), switch_(false) {
}

EndgameRenderer::~EndgameRenderer() {
}

void EndgameRenderer::onKeyDown(unsigned char key, int x, int y) {
  if (key == ' ' || key == 13) switch_ = true;
}

bool EndgameRenderer::shouldKeysRepeat() const {
  return false;
}

NextAction EndgameRenderer::renderOverBackground() {
  if (switch_) {
    return RA_END_TO_FADE;
  } else {
    return RA_REDISPLAY;
  }
}

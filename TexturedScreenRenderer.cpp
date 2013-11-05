// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class TexturedScreenRenderer and related constructs.
#include "TexturedScreenRenderer.h"
#include "readtex.h"
#include "Config.h"
#include "ColorSpec.h"

TexturedScreenRenderer::TexturedScreenRenderer(const char* filename) {
  glGenTextures(1, ssTexName_);
  glBindTexture(GL_TEXTURE_2D, ssTexName_[0]);
  LoadRGBMipmaps(filename, GL_RGB);
}

TexturedScreenRenderer::~TexturedScreenRenderer() {
  glDeleteTextures(1, ssTexName_);
}

void TexturedScreenRenderer::init() {
  glClearColor(Config::SKY_COLOR->r(), Config::SKY_COLOR->g(), Config::SKY_COLOR->b(), Config::SKY_COLOR->a());
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH_TEST);
}

void TexturedScreenRenderer::reshape(int newWidth, int newHeight) {
  gluOrtho2D(0.0, Config::MAX_2D_COORD, 0.0, Config::MAX_2D_COORD);
}

NextAction TexturedScreenRenderer::render() {
  glPushMatrix();
  glPushAttrib(GL_TEXTURE_BIT);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ssTexName_[0]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  glBegin(GL_QUADS);
    glTexCoord2f(0, 0);        
    glVertex3d(0, 0, 0); 
    glTexCoord2f(0, 1);        
    glVertex3d(0, Config::MAX_2D_COORD, 0); 
    glTexCoord2f(1, 1);        
    glVertex3d(Config::MAX_2D_COORD, Config::MAX_2D_COORD, 0); 
    glTexCoord2f(1, 0);        
    glVertex3d(Config::MAX_2D_COORD, 0, 0); 
  glEnd();

  NextAction action = renderOverBackground();

  glPopAttrib();
  glPopMatrix();

  return action;
}

NextAction TexturedScreenRenderer::renderOverBackground() {
  return RA_REDISPLAY;
}

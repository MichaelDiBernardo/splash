// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class FadeRenderer and related constructs.
#include "FadeRenderer.h"
#include "os.h"
#include "Config.h"
#include "Timer.h"

FadeRenderer::FadeRenderer(int secondsToFade, NextAction doneAction, Renderer* sceneToFade) 
  : durationBefore_(0),
    duration_(secondsToFade * 1000), 
    doneAction_(doneAction), 
    target_(sceneToFade), 
    fadeTimer_(new Timer()) {
  fadeTimer_->start();
}

FadeRenderer::FadeRenderer(int secondsBeforeFade, int secondsToFade, NextAction doneAction, Renderer* sceneToFade) 
  : durationBefore_(secondsBeforeFade * 1000),
    duration_(secondsToFade * 1000), 
    doneAction_(doneAction), 
    target_(sceneToFade), 
    fadeTimer_(new Timer()) {
  fadeTimer_->start();
}
FadeRenderer::~FadeRenderer() {
  delete target_;
  delete fadeTimer_;
}

void FadeRenderer::init() {
}

NextAction FadeRenderer::render() {
  target_->render();

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, Config::MAX_2D_COORD, 0, Config::MAX_2D_COORD);

  glMatrixMode(GL_MODELVIEW);
  
  double elapsed = fadeTimer_->getTimeInMilliseconds();
  double fadeFactor = (elapsed - durationBefore_) / duration_;
  if (fadeFactor < 0.0) fadeFactor = 0.0;
  glColor4d(0, 0, 0, fadeFactor);

  glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(Config::MAX_2D_COORD, 0, 0);
    glVertex3f(Config::MAX_2D_COORD, Config::MAX_2D_COORD, 0);
    glVertex3f(0, Config::MAX_2D_COORD, 0);
  glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  if (elapsed > (duration_ + durationBefore_)) {
    return doneAction_;
  } else {
    return RA_REDISPLAY;
  }
}

void FadeRenderer::reshape(int newWidth, int newHeight) {
  target_->reshape(newWidth, newHeight);
}

void FadeRenderer::onKeyDown(unsigned char key, int x, int y) {
  target_->onKeyDown(key, x, y);
}

void FadeRenderer::onKeyUp(unsigned char key, int x, int y) {
  target_->onKeyUp(key, x, y);
}

void FadeRenderer::onSpecialKeyDown(int key, int x, int y) {
  target_->onSpecialKeyDown(key, x, y);
}

void FadeRenderer::onSpecialKeyUp(int key, int x, int y) {
  target_->onSpecialKeyUp(key, x, y);
}

bool FadeRenderer::shouldKeysRepeat() const {
  return target_->shouldKeysRepeat();
}

const Renderer& FadeRenderer::getRenderer() const {
  return *target_;
}

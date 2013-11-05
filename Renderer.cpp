// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class Renderer and related constructs.
#include "Renderer.h"
#include "os.h"

Renderer::Renderer() : enabled_(true) {
}

Renderer::~Renderer() {
}

void Renderer::init() {
}

NextAction Renderer::render() {
  return RA_NONE;
}

void Renderer::reshape(int newWidth, int newHeight) {
}

void Renderer::onKeyDown(unsigned char key, int x, int y) {
}

void Renderer::onKeyUp(unsigned char key, int x, int y) {
}

void Renderer::onSpecialKeyDown(int key, int x, int y) {
}

void Renderer::onSpecialKeyUp(int key, int x, int y) {
}

bool Renderer::shouldKeysRepeat() const {
  return false;
}

void Renderer::disable() {
  enabled_ = false;
}

void Renderer::enable() {
  enabled_ = true;
}

bool Renderer::isEnabled() const {
  return enabled_;
}

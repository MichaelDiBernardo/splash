#include "EngineInput.h"

EngineInput::EngineInput() : mf_(false), mb_(false), tl_(false), tr_(false) {
}

EngineInput::~EngineInput() {
}

void EngineInput::setPlayerMovingForward(bool b) {
  mf_ = b;
}

void EngineInput::setPlayerMovingBackward(bool b) {
  mb_ = b;
}

void EngineInput::setPlayerTurningLeft(bool b) {
  tl_ = b;
}

void EngineInput::setPlayerTurningRight(bool b) {
  tr_ = b;
}

bool EngineInput::playerMovingForward() const {
  return mf_;
}

bool EngineInput::playerMovingBackward() const {
  return mb_;
}

bool EngineInput::playerTurningLeft() const {
  return tl_;
}

bool EngineInput::playerTurningRight() const {
  return tr_;
}

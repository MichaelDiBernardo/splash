// Implementation of class DinoState.
#include "DinoState.h"
#include "os.h"
#include "Orientation.h"
#include "Config.h"
#include <math.h>

DinoState::DinoState(const Orientation& initO, CharacterType myType) 
  : moveVelocity_(0), 
    turnVelocity_(0), 
    motionState_(NOT_ACCELERATING), 
    turnState_(NOT_TURNING), 
    myCharType_(myType),
    myO_(initO) { 
  if (myCharType_ == CHAR_PC) {
    mp_ = new MotionParams(
        &Config::PLAYER_FORWARD_ACCELERATION, 
        &Config::PLAYER_MAX_FORWARD_VELOCITY,
        &Config::PLAYER_BACKWARD_ACCELERATION, 
        &Config::PLAYER_MAX_BACKWARD_VELOCITY,
        &Config::PLAYER_TURN_VELOCITY);
  } else {
    mp_ = new MotionParams(
        &Config::BOT_FORWARD_ACCELERATION, 
        &Config::BOT_MAX_FORWARD_VELOCITY,
        &Config::BOT_BACKWARD_ACCELERATION, 
        &Config::BOT_MAX_BACKWARD_VELOCITY,
        &Config::BOT_TURN_VELOCITY);
  }
}

DinoState::DinoState(const DinoState& d) {
  moveVelocity_ = d.moveVelocity_;
  turnVelocity_ = d.turnVelocity_;
  motionState_ = d.motionState_;
  turnState_ = d.turnState_;
  myCharType_ = d.myCharType_;
  myO_ = d.getOrientation();
  mp_ = new MotionParams();
  // Shallow copy works just fine.
  *mp_ = *(d.mp_);
}

DinoState::~DinoState() {
  delete mp_;
}

CharacterType DinoState::getType() const {
  return myCharType_;
}

void DinoState::setMovingForward() {
  motionState_ = ACCELERATING_FORWARD;

  moveVelocity_ += *(mp_->forwardAcceleration);

  if (moveVelocity_ > *(mp_->maxForwardVelocity))
    moveVelocity_ = *(mp_->maxForwardVelocity);
}

void DinoState::setMovingBackward() {
  motionState_ = ACCELERATING_BACKWARD;

  moveVelocity_ += *(mp_->backwardAcceleration);

  if (moveVelocity_ < *(mp_->maxBackwardVelocity))
    moveVelocity_ = *(mp_->maxBackwardVelocity);
}

void DinoState::stopMoving() {
  motionState_ = NOT_ACCELERATING;
  if (moveVelocity_ > 0) {
    moveVelocity_ -= Config::PLAYER_DRAG;
    if (moveVelocity_ < 0) moveVelocity_ = 0;
  }
  else {
    moveVelocity_ += Config::PLAYER_DRAG;
    if (moveVelocity_ > 0) moveVelocity_ = 0;
  }
}

void DinoState::setTurningLeft() {
  turnState_ = TURNING_LEFT;
  turnVelocity_ = -1 * (*(mp_->turnVelocity));
}

void DinoState::setTurningRight() {
  turnState_ = TURNING_RIGHT;
  turnVelocity_ = *(mp_->turnVelocity);
}

void DinoState::stopTurning() {
  turnState_ = NOT_TURNING;
  turnVelocity_ = 0;
}

const Orientation& DinoState::getOrientation() const {
  return myO_;
}

void DinoState::evolve(PowerupEffect e) {
  // update angle (IN RADIANS!)
  double curTurnVelocity = turnVelocity_;
  double curMoveVelocity = moveVelocity_;

  if (myCharType_ == CHAR_PC && e == PE_SPEED) {
    curTurnVelocity *= 2;
    curMoveVelocity *= 2;
  }
  else if (myCharType_ == CHAR_NPC && e == PE_FREEZE) {
    curTurnVelocity = 0;
    curMoveVelocity = 0;
  }
  else if (myCharType_ == CHAR_NPC && e == PE_FEAR) {
    curTurnVelocity *= -1;
  }
  
  myO_.addToAngle(curTurnVelocity);

  // compute increments
  double x_increment = curMoveVelocity * cos(myO_.getAngle());
  double y_increment = curMoveVelocity * sin(myO_.getAngle());

  myO_.addToX(x_increment);
  myO_.addToY(y_increment);
}

void DinoState::clipPosition(double minX, double minY, double maxX, double maxY) {
  if (minX > myO_.getX()) myO_.setX(0);
  if (minY > myO_.getY()) myO_.setY(0);
  
  if (maxX < myO_.getX()) myO_.setX(maxX);
  if (maxY < myO_.getY()) myO_.setY(maxY);
}

LateralMotionState DinoState::getMotionState() const {
  return motionState_;
}

AngularMotionState DinoState::getTurningState() const {
  return turnState_;
}

bool DinoState::isHittingOtherDino(const DinoState& fatso) const {
  const Orientation& c1 = getOrientation();
  const Orientation& c2 = fatso.getOrientation();

  double c1c2x = c2.getX() - c1.getX();
  double c1c2y = c2.getY() - c1.getY();

  // heehee
  double d = sqrt(c1c2x*c1c2x + c1c2y*c1c2y);
  double residual = 2 * Config::DINO_RADIUS - d;

  if (residual > 0)   return true;
  else                return false;
}

void DinoState::crashWithDino(DinoState* fatso) {
  Orientation& c1 = myO_;
  // This is the only method in the game that requires mutating an external
  // state's orientation, so I didn't feel like it would be good to make a
  // getMutableOrientation method on DinoState just to accommodate this single
  // case. Thus, we grab at the other state's private orientation directly.
  Orientation& c2 = fatso->myO_;

  double c1c2x = c2.getX() - c1.getX();
  double c1c2y = c2.getY() - c1.getY();

  // Only duplicated twice -- not a target for refactoring yet :)
  double d = sqrt(c1c2x*c1c2x + c1c2y*c1c2y);
  double residual = 2 * Config::DINO_RADIUS - d;

  // No collision, get out...
  if (residual <= 0)   return;

  double nc1c2x = c1c2x/2*d;
  double nc1c2y = c1c2y/2*d;
  
  c1.setX(c1.getX() - nc1c2x);
  c1.setY(c1.getY() - nc1c2y);

  c2.setX(c2.getX() + nc1c2x);
  c2.setY(c2.getY() + nc1c2y);
}

void DinoState::setOrientation(const Orientation& newO) {
  myO_ = newO;
}

#include "Orientation.h"
#include <math.h>

Orientation::Orientation() : myX_(0), myY_(0), myAngle_(0) {
}

Orientation::Orientation(double initX, double initY, double angle)
  : myX_(initX), myY_(initY), myAngle_(angle) {
}

Orientation::Orientation(const Orientation& o) {
  myX_ = o.getX();
  myY_ = o.getY();
  myAngle_ = o.getAngle();
}

Orientation::~Orientation() {
}

double Orientation::getX() const {
  return myX_;
}

double Orientation::getY() const {
  return myY_;
}

double Orientation::getAngle() const {
  return myAngle_;
}

void Orientation::setX(double newX) {
  myX_ = newX;
}

void Orientation::setY(double newY) {
  myY_ = newY;
}

void Orientation::setAngle(double newAngle) {
  myAngle_ = newAngle;
}

void Orientation::addToX(double increment) {
  myX_ += increment;
}

void Orientation::addToY(double increment) {
  myY_ += increment;
}

void Orientation::addToAngle(double increment) {
  myAngle_ += increment;
  while (myAngle_ > 2*M_PI) myAngle_ -= 2*M_PI;
  while (myAngle_ < 0) myAngle_ += 2*M_PI;
}

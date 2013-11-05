#include "ColorSpec.h"
ColorSpec::ColorSpec(float red, float green, float blue, float alpha)
  : myr_(red), myg_(green), myb_(blue), mya_(alpha) {
}
    
ColorSpec::ColorSpec(float red, float green, float blue)
  : myr_(red), myg_(green), myb_(blue), mya_(1.0f) {
}
    
ColorSpec::ColorSpec()
  : myr_(0.0f), myg_(0.0f), myb_(0.0f), mya_(1.0f) {
}

ColorSpec::~ColorSpec() {
}

float ColorSpec::r() const {
  return myr_;
}

float ColorSpec::g() const {
  return myg_;
}

float ColorSpec::b() const {
  return myb_;
}

float ColorSpec::a() const {
  return mya_;
}

void ColorSpec::set() const {
  glColor4f(myr_, myg_, myb_, mya_);
}

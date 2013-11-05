// Convenience class to deal with colors.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __COLOR_SPEC_H__
#define __COLOR_SPEC_H__

#include "Basics.h"
#include "os.h"

class ColorSpec {
 public:
  ColorSpec(float red, float green, float blue, float alpha);
  ColorSpec(float red, float green, float blue);
  ColorSpec();
  ~ColorSpec();

  float r() const;
  float g() const;
  float b() const;
  float a() const;

  // Issue the OpenGL commands to change the current color to this.
  void set() const;

 private:
  float myr_;
  float myg_;
  float myb_;
  float mya_;

  DISALLOW_EVIL_CONSTRUCTORS(ColorSpec);
};
#endif

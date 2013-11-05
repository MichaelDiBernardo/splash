// A single frame in an animation for our model. Represents both key and
// interpolated frames.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// 1. Assignment spec.
// 2. Foster, Garret. "Understanding and Implementing Scene Graphs."
//    Available online at http://www.gamedev.net/reference/programming/features/scenegraph/
#ifndef __FRAME_H__
#define __FRAME_H__

#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
using std::ifstream;

class Frame {
 public:
  // Construct a new Frame given a pointer to the beginning of a keyframe
  // record in a file. Advances the given input by a single Frame record, and
  // does NOT take ownership of the given stream.
  // This should really be a static factory function so that we can throw
  // errors without dying, but pretty much any error in this process will
  // require the program to die anyways, so it's no big loss...
  explicit Frame(ifstream* fp);

  // Constructs a new Frame with uninitialized values for its fields. Used
  // by overloaded operators. 
  explicit Frame(int numFields);

  // Copy constructor.
  Frame(const Frame& rhs);

  // Frees this keyframe. Doesn't really do anything.
  ~Frame();

  // Gets the number of fields in this frame (ie the number of parameters
  // recorded for it).
  int getNumFields() const;

  // Returns the list of field values that compose this frame.
  const double* getFields() const;

  // Returns when this frame is supposed to occur in the sequence of animation.
  // Units are milliseconds.
  unsigned long getTimeInMS() const;

  // Vector addition.
  Frame operator+(const Frame& rhs) const;

  // Vector subtraction.
  Frame operator-(const Frame& rhs) const;

  // Scalar multiplication.
  Frame operator*(double scalar) const; 

 private:
  // What time is this frame supposed to be displayed at?
  unsigned long time_;
  // What are the values of all the joint angles etc.?
  double* fields_;
  // How many fields are there?
  int numFields_;
};

#endif

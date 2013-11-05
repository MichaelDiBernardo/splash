// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// A grab bag of 2D drawing functions.
#ifndef __2DUTILS_H__
#define __2DUTILS_H__

#include <string>
using std::string;

class Utils2D {
 public:
  // Draw a circle of radius 'r' around the origin. The circle is a convex
  // polygon composed of 'slices' wedges.
  static void drawCircle(double radius, int slices);
  
  // Draw a string in Roman stroke font starting at the origin. See 'man
  // glutStrokeCharacter' for information on how many units each character is;
  // as of this writing, they are (very) roughly 100 units square.
  static void drawString(const string& s);

  // Draw a string in Roman stroke font starting at the given X/Y coordinates. 
  static void drawString(const string& s, double x, double y);

  // Draws a shiny ball! Setting the color beforehand will change the color of
  // the ball, but the color of the speckle is fixed.
  static void drawShinyBall(double radius);

 private:
  // Don't let anyone instantiate me.
  Utils2D();
};

#endif

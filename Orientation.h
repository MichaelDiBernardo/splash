// A combined position and facing angle. The angle is the counterclockwise
// angle from east "axis".
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __ORIENTATION_H__
#define __ORIENTATION_H__

class Orientation {
 public:
  // Constructs an orientation at 0,0 facing east.
  Orientation();

  // Constructs an orientation with the given init values.
  Orientation(double initX, double initY, double angle);

  // Copy constructor.
  Orientation(const Orientation& o);

  // Frees resources used by this object.
  ~Orientation();

  double getX() const;
  double getY() const;
  double getAngle() const;

  void setX(double newX);
  void setY(double newY);
  void setAngle(double newAngle);

  void addToX(double increment);
  void addToY(double increment);
  void addToAngle(double increment);

 private:
  // My x coordinate.
  double myX_;
  // My y coordinate.
  double myY_;
  // Angle from the east axis (just like in trig class :)
  double myAngle_;
};

#endif

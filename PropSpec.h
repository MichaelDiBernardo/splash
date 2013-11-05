// Stores the ID, type, dimensions, and position of a prop in the field.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __PROP_SPEC_H__
#define __PROP_SPEC_H__

#include "Basics.h"

class Orientation;

enum PropType {
  ISLAND_PROP, 
  TROPHY_PROP,
  THRONE_PROP,
  TORCH_PROP,
  BOX_PROP,
  DOT_PROP,
  FEAR_POWERUP_PROP,
  FREEZE_POWERUP_PROP,
  SPEED_POWERUP_PROP
}; 

class PropSpec {
 public:
  // Constructs a prop with the given stats.
  PropSpec(int id, PropType p, double xPos, double yPos, double xDim, double yDim);

  // Frees resources used by this object.
  ~PropSpec();

  int getID() const;
  PropType getType() const;

  double getXPos() const;
  double getYPos() const;

  double getXDim() const;
  double getYDim() const;

  // Does the bounding box of this prop contain the given point?
  bool contains(const Orientation& o) const;

  // Is this prop currently part of the model?
  bool isActive() const;

  // Clips the given orientation out of the bounding box.
  Orientation clip(const Orientation& toClip) const;

  // Includes or excludes this prop from the model.
  void setActive(bool flag);

 private:
  // Prop id as given in the spec file.
  int myID_;
  // Type of this prop.
  PropType myType_;
  // My positional/dimensional attributes.
  double myXPos_;
  double myYPos_;
  double myXDim_;
  double myYDim_;
  // Is this prop "active" (i.e. if a dot, powerup, etc. is it still in play?)
  bool active_;

  DISALLOW_EVIL_CONSTRUCTORS(PropSpec);
};

#endif

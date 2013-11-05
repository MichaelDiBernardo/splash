// Input from the control environment to the state machine that 
// models the gameworld.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __ENGINE_INPUT_H__
#define __ENGINE_INPUT_H__

#include "Basics.h"

class EngineInput {
 public:
  // Creates a collection of states where all bits are 0.
  EngineInput();

  // Frees resources used by this object.
  ~EngineInput();

  // Getters and setters for control inputs.
  void setPlayerMovingForward(bool b);
  void setPlayerMovingBackward(bool b);
  void setPlayerTurningLeft(bool b);
  void setPlayerTurningRight(bool b);

  bool playerMovingForward() const;
  bool playerMovingBackward() const;
  bool playerTurningLeft() const;
  bool playerTurningRight() const;

 private:
  // Moving forward?
  bool mf_;
  // Moving backward?
  bool mb_;
  // Turning left?
  bool tl_;
  // Turning right?
  bool tr_;

  DISALLOW_EVIL_CONSTRUCTORS(EngineInput);
};

#endif

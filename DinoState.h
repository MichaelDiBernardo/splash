// DinoState.h
// 
// State of a single character in the game.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __DINO_STATE_H__
#define __DINO_STATE_H__

#include "Basics.h"
#include "Orientation.h"

// State enumerations for character states.
enum LateralMotionState { ACCELERATING_FORWARD, ACCELERATING_BACKWARD, NOT_ACCELERATING };
enum AngularMotionState { TURNING_LEFT, TURNING_RIGHT, NOT_TURNING };
enum CharacterType  { CHAR_PC, CHAR_NPC };
enum PowerupEffect { PE_NONE, PE_SPEED, PE_FEAR, PE_FREEZE };

class DinoState {
 public:
  // Creates a new agent state where the agent is initialized to be
  // positioned according to the given orientation. 
  DinoState(const Orientation& initO, CharacterType myType);

  // Copy constructor: I don't use these very often, but it's useful here.
  DinoState(const DinoState& d);

  // Frees the resources used by this state object.
  ~DinoState();

  // Evolves the dinosaur state by one timestep. 
  void evolve(PowerupEffect e);

  // Constrains the dinosaur to remain within the given 
  // coordinate ranges. If the dino is outside of the given rectangle,
  // it will be moved to an appropriate location on the periphery.
  void clipPosition(double minX, double minY, double maxX, double maxY);

  // Is the given dino hitting this one?
  bool isHittingOtherDino(const DinoState& fatso) const;

  // Repositions dinos so they're not hitting each other. Both this dino
  // and the given dino will be mutated by this procedure.
  //
  // If you call this and the two dinos aren't actually touching, this will
  // terminate without actually computing displacements (ie it will check the
  // intersection and then bail).
  void crashWithDino(DinoState* fatso);

  // Gets the orientation of the dinosaur maintained by this state.
  const Orientation& getOrientation() const;

  // Change the orientation of this dino.
  void setOrientation(const Orientation& newO);

  // Setters for dino states.
  void setMovingForward();
  void setMovingBackward();
  void stopMoving();

  void setTurningLeft();
  void setTurningRight();
  void stopTurning();

  // Getters for character states.
  CharacterType getType() const;

  // Is this dino accelerating forward, accelerating backward, or 
  // not accelerating at all?
  LateralMotionState getMotionState() const;

  // Is this dino turning left, turning right, or not turning at all?
  AngularMotionState getTurningState() const;

 private:
  struct MotionParams {
    // These are pointers to doubles because values for these parameters may
    // change in Config as the game is played.
    const double* forwardAcceleration;
    const double* maxForwardVelocity;
    const double* backwardAcceleration;
    const double* maxBackwardVelocity;
    const double* turnVelocity;
    MotionParams() {};
    MotionParams(double* fa, double* mfv, double* ba, double* mbv, double* tv)
      : forwardAcceleration(fa), maxForwardVelocity(mfv), 
        backwardAcceleration(ba), maxBackwardVelocity(mbv), turnVelocity(tv) {}
  };

  // Acceleration rates and velocity limits for this dino.
  MotionParams* mp_;
  // Forward velocity of the dino.
  double moveVelocity_;
  // Turning velocity of the dino.
  double turnVelocity_;

  // The way the dino is moving.
  LateralMotionState motionState_;
  // The way the dino is turning.
  AngularMotionState turnState_;
  // The type of the character.
  CharacterType myCharType_;
  // Position info for the dino.
  Orientation myO_;
};

#endif

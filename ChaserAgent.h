// A "brain" for the enemy dinos.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __CHASER_AGENT_H__
#define __CHASER_AGENT_H__
class DinoState;

#include "os.h"

class ChaserAgent {
 public:
  // Construct a new chaser agent to control the given dino state. That is, the
  // agent controls the slave in such a way that it will try to chase the given
  // target.
  ChaserAgent(const DinoState& target, DinoState* slave);

  // Frees resources.
  ~ChaserAgent();

  // Provides inputs to slave state.
  void control();

 private:
  // Dinosaur that this agent will chase.
  const DinoState& target_;  
  // Dinosaur that the agent controls.
  DinoState* controlled_;
};

#endif

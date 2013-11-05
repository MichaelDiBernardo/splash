// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// A node in the scene graph that renders the 2D widgets that supply game
// metadata to the user. Otherwise known as a "heads-up display". 
#ifndef __HUDNODE_H__
#define __HUDNODE_H__

#include <string>
using std::string;
#include "Basics.h"
#include "SceneNode.h"

class Engine;
class Timer;

class HUDNode : public SceneNode {
 public:
  
  // Create a new HUD that acts as a view on the given model. The startupTimer
  // is used to produce the countdown at the game beginning.
  HUDNode(const string& id, const Engine& model, const Timer& startupTimer);

  // Free resources used by this node.
  ~HUDNode();

  // Render the HUD.
  virtual void render();

 private:
  // The model being watched.
  const Engine& model_;
  // String that holds the par time: This never changes, so we store it once.
  string parString_;
  // Timer that we should watch to render countdown at start.
  const Timer& startupTimer_;

  DISALLOW_EVIL_CONSTRUCTORS(HUDNode);
};

#endif

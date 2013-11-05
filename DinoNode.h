// Node in scene graph that draws a dino.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __DINO_NODE_H__
#define __DINO_NODE_H__
class Animation;
class DinoState;
class JointNode;
class Orientation;

#include "Basics.h"
#include "AquaDino.h"
#include "SceneNode.h"
#include <string>
using std::string;

class DinoNode : public SceneNode {
 public:
  // New dino node.
  DinoNode(const string& id, const DinoState& myState);

  // Purge the subtree rooted at this node, including this node.
  virtual ~DinoNode();

  // Gets the orientation of this node.
  // TODO: See if this is actually used.
  const Orientation& getOrientation() const;

  // Render this node and all of its children. 
  virtual void render();

 private:
  SceneNode* dinoRoot_;
  JointNode* joints_[AQUA_DINO_NUM_JOINTS]; // List of dino joints
  const DinoState& state_;

  Animation* mf_;  // move forward
  Animation* mb_;  // move backward
  Animation* tl_;  // turn left
  Animation* tr_;  // turn right

  Animation* currentAnimation_;

  // Helper method to build dino model.
  SceneNode* buildDino();

  // Helper method to assign new frames.
  void animate();

  DISALLOW_EVIL_CONSTRUCTORS(DinoNode);

};

#endif

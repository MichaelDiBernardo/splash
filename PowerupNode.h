// Node in scene graph that draws a 'dot'.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.

#ifndef __POWERUP_NODE_H__
#define __POWERUP_NODE_H__

#include "os.h"
#include "PropNode.h"
#include <string>
using namespace std;

class PowerupNode : public PropNode {

 public:

  // New powerup node.
  PowerupNode(const string& id, GLenum lightIndex, const PropSpec& initSpec);

  // Purge the subtree rooted at this node, including this node.
  virtual ~PowerupNode();

  // Render this node and all of its children.
  virtual void render();

 private:
  double myRot_;
  GLenum myLight_;
};

#endif

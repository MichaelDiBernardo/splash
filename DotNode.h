// Node in scene graph that draws a 'dot'.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __DOT_NODE_H__
#define __DOT_NODE_H__
#include "Basics.h"
#include "PropNode.h"
#include <string>
using std::string;

class DotNode : public PropNode {
 public:
  // New dot node.
  DotNode(const string& id, const PropSpec& initSpec);

  // Purge the subtree rooted at this node, including this node.
  virtual ~DotNode();

  // Render this node and all of its children. 
  virtual void render();

private:
  // Change in height for next frame.
  double delta_h_;
  // Change in velocity for next frame.
  double delta_hv_;
  // My display list index.
  int myDList_;

  DISALLOW_EVIL_CONSTRUCTORS(DotNode);
};

#endif

// Node in scene graph that draws a box obstacle.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __BOX_NODE_H__
#define __BOX_NODE_H__

#include "Basics.h"
#include "PropNode.h"
#include <string>
using std::string;

class BoxNode : public PropNode {
 public:
  // New box node.
  BoxNode(const string& id, GLuint myTex, const PropSpec& initSpec);

  // Purge the subtree rooted at this node, including this node.
  virtual ~BoxNode();

  // Render this node and all of its children. 
  virtual void render();

 private:
  // My texture index.
  GLuint myTex_;

  DISALLOW_EVIL_CONSTRUCTORS(BoxNode);
};

#endif

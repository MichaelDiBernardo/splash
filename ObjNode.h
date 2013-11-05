// Node in scene graph that draws an obstacle from an OBJ model.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __OBJ_NODE_H__
#define __OBJ_NODE_H__

#include <string>
using std::string;
#include "Basics.h"
#include "PropNode.h"

class ObjNode : public PropNode {
 public:
  // New OBJ node.
  ObjNode(const string& id, const PropSpec& initSpec);

  // Purge the subtree rooted at this node, including this node.
  virtual ~ObjNode();

  // Render this node and all of its children. 
  virtual void render();

private:
  // My display list index.
  int myList_;

  DISALLOW_EVIL_CONSTRUCTORS(ObjNode);
};

#endif

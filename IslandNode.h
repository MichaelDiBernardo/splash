// Node in scene graph that draws an island obstacle.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __ISLAND_NODE_H__
#define __ISLAND_NODE_H__

#include <string>
using std::string;
#include "Basics.h"
#include "PropNode.h"
#include "os.h"

class IslandNode : public PropNode {
 public:
  // New island node.
  IslandNode(const string& id, GLuint myTex, const PropSpec& initSpec);

  // Purge the subtree rooted at this node, including this node.
  virtual ~IslandNode();

  // Render this node and all of its children. 
  virtual void render();

 private:
  // How tall is this island?
  double height_;
  // Texture index for the sand texture.
  GLuint myTex_;
  // Ellipsoid properties of island.
  GLUquadric* myQuadProperties_;

  DISALLOW_EVIL_CONSTRUCTORS(IslandNode);
};

#endif

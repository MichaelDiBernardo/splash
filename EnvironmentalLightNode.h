// Node in scene graph that represents some sort of environmental light
// with a fixed position (ie sun, moon).
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __ENVIRONMENTAL_LIGHT_NODE_H__
#define __ENVIRONMENTAL_LIGHT_NODE_H__

#include "Basics.h"
#include "SceneNode.h"
#include <string>
using std::string;

class EnvironmentalLightNode : public SceneNode {
 public:
  // Creates a new light high in the sky above x, y :D
  EnvironmentalLightNode(const string& id, double x, double y);

  // Purge the subtree rooted at this node, including this node.
  virtual ~EnvironmentalLightNode();

  // Render this node and all of its children. 
  virtual void render();

 private:
  // Where am I?
  double myX_;
  double myY_;

  DISALLOW_EVIL_CONSTRUCTORS(EnvironmentalLightNode);
};

#endif

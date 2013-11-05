// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Node to render a game 'prop' i.e. non-wall, non-island obstacles, powerups,
// and dots.
#ifndef __PROPNODE_H__
#define __PROPNODE_H__

#include <string>
using std::string;
#include "Basics.h"
#include "SceneNode.h"

class PropSpec;

class PropNode : public SceneNode {
 public:
  // Creates a new prop view with the given ID and spec. Specs must be
  // externally maintained and must persist for the lifetime of this object.
  PropNode(const string& id, const PropSpec& spec);

  // Frees resources used by this node.
  virtual ~PropNode();

 protected: 
  // Description of prop to render.
  const PropSpec& myProp_;

  DISALLOW_EVIL_CONSTRUCTORS(PropNode);
};

#endif

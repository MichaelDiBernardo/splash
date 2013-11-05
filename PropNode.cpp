// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class PropNode and related constructs.
#include "PropNode.h"

PropNode::PropNode(const string& id, const PropSpec& spec) 
  : SceneNode(id), myProp_(spec) {
}

PropNode::~PropNode() {
}

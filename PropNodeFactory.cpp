// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class PropNodeFactory and related constructs.
#include "PropNodeFactory.h"
#include <assert.h>
#include "BoxNode.h"
#include "DotNode.h"
#include "IslandNode.h"
#include "ObjNode.h"
#include "PowerupNode.h"
#include "PropNode.h"
#include "PropSpec.h"

PropNodeFactory::PropNodeFactory(GLuint islandTexture, GLuint boxTexture) 
  : islandTexture_(islandTexture), boxTexture_(boxTexture) {
  lights_.push(GL_LIGHT7);
  lights_.push(GL_LIGHT6);
  lights_.push(GL_LIGHT5);
  lights_.push(GL_LIGHT4);
  lights_.push(GL_LIGHT3);
  lights_.push(GL_LIGHT2);
  lights_.push(GL_LIGHT1);
}

PropNodeFactory::~PropNodeFactory() {
}

PropNode* PropNodeFactory::createNodeFor(const PropSpec& p) const {
  if (p.getType() == ISLAND_PROP)
    return new IslandNode("ISLAND", islandTexture_, p);
  else if (p.getType() == BOX_PROP)
    return new BoxNode("BOX", boxTexture_, p);
  else if (p.getType() == TORCH_PROP)
    return new ObjNode("TORCH", p);
  else if (p.getType() == THRONE_PROP)
    return new ObjNode("THRONE", p);
  else if (p.getType() == TROPHY_PROP)
    return new ObjNode("TROPHY", p);
  else if (p.getType() == DOT_PROP) 
    return new DotNode("DOT", p);
  else if (p.getType() == FEAR_POWERUP_PROP || SPEED_POWERUP_PROP || FREEZE_POWERUP_PROP) {
    assert(lights_.size() > 0);
    GLenum next_light = lights_.top();
    lights_.pop();
    return new PowerupNode("POWERUP", next_light, p);
  }
  else 
    assert(false);
}

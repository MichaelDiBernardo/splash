// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Factory to manufacture PropNodes based on given specs.
#ifndef __PROPNODEFACTORY_H__
#define __PROPNODEFACTORY_H__

#include <stack>
using std::stack;
#include "Basics.h"
#include "os.h"

class PropSpec;
class PropNode;

class PropNodeFactory {
 public:
  // Create a new factory, that will assign islandTexture to IslandNodes and
  // boxTexture to new BoxNodes.
  PropNodeFactory(GLuint islandTexture, GLuint boxTexture);

  // Free resources used by this factory.
  ~PropNodeFactory();

  // Create a node for the given spec. Caller takes ownership of the object.
  PropNode* createNodeFor(const PropSpec& spec) const;
  
 private:
  // Texture index of the island texture.
  GLuint islandTexture_;
  // Texture index of the box texture.
  GLuint boxTexture_;
  // The lights that we have available to assign to powerups. This is mutable
  // so that we can pop the stack and still make createNodeFor a const
  // operation.
  mutable stack<GLenum> lights_;

  DISALLOW_EVIL_CONSTRUCTORS(PropNodeFactory);
};

#endif

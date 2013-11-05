// Node in scene graph that draws ocean scenery.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __SETTING_NODE_H__
#define __SETTING_NODE_H__

#include <string>
using std::string;

#include "SceneNode.h"
#include "Basics.h"
#include "os.h"

class SettingNode : public SceneNode {
 public:
  // Constructs a new setting.
  SettingNode(const string& id, double worldWidth, double worldHeight, GLuint
              floorTexInd, GLuint skyTexInd);

  // Purge the subtree rooted at this node, including this node.
  virtual ~SettingNode();

  // Render this node and all of its children. 
  virtual void render();

 private:
  // Width of the scene (X axis).
  double width_;
  // "Height" of the scene (Z axis).
  double height_;
  // Texture index for floor.
  GLuint floorInd_;
  // Texture index for sky. (Currently not being used.)
  GLuint skyInd_;
};

#endif

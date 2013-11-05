// A very general description of a component in our scene. Manages
// the addition and updating of child nodes. 
//
// I implement the scene graph by using the composite design pattern.
// The SceneNode is the base type in the composite structure.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// 1. Angel, Edward. "Interactive Computer Graphics", third ed., 444-62. 
// 2. Foster, Garret. "Understanding and Implementing Scene Graphs."
//    Available online at http://www.gamedev.net/reference/programming/features/scenegraph/
#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <list>
#include <string>
using std::list;
using std::string;

#include "os.h"
#include "Basics.h"

class SceneNode {
 public:
  // Construct a new scene node.
  explicit SceneNode(const string& id);

  // Purge the subtree rooted at this node, including this node.
  virtual ~SceneNode();

  // Render this node and all of its children. 
  virtual void render();

  // Get the name/ID of this node.
  const string& getID() const;

  // Add a child node to this node. Takes ownership of the given node.
  virtual void addChild(SceneNode* child);

  // How many children does this node have?
  int getNumChildren() const;

 private:
  // My children.
  list<SceneNode*> children_;
  // My id.
  string id_;

  DISALLOW_EVIL_CONSTRUCTORS(SceneNode);
};

#endif

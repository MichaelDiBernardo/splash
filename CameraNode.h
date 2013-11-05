// Node in scene graph that makes sure camera is always looking at
// player. 
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// None.
#ifndef __CAMERA_NODE_H__
#define __CAMERA_NODE_H__

#include "Basics.h"
#include "SceneNode.h"
#include "os.h"
#include <string>
using std::string;
class DinoNode;

class CameraNode : public SceneNode {
 public:
  // Construct a new camera node looking at the given dino.
  CameraNode(const string& id, const DinoNode& target);

  // Purge the subtree rooted at this node, including this node.
  virtual ~CameraNode();

  // Zooms camera in.
  void zoomIn();

  // Zooms camera out.
  void zoomOut();

  // Raises the camera.
  void raise();

  // Lowers the camera.
  void lower();

  // Render this node and all of its children. 
  virtual void render();

 private:
  // Dino to focus on.
  const DinoNode& focus_;
  // How far away from the target dino is the camera?
  double followDistance_;
  // How high above the 'surface' is the camera?
  double camH_;

  DISALLOW_EVIL_CONSTRUCTORS(CameraNode);
};

#endif

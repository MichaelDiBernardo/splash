// Responsible for maintaining graphical representation of model state
// and drawing that representation when a new frame is requested.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
using std::list;
#include "Basics.h"

class CameraNode;
class DinoNode;
class Engine;
class SceneNode;
class Timer;

class Scene {
 
 public:
  // Creates a scene that will render based on the state of the given engine.
  // Basically, the scene is a view of the state of the engine. The
  // startupTimer is used to produce the countdown at the beginning of the
  // level (3... 2... 1... GO), and is maintained by the GameplayRenderer.
  explicit Scene(const Engine& model, const Timer& startupTimer);

  // Frees resources used by the scene.
  ~Scene();

  // Zooms the camera out by a single increment.
  void zoomOut();

  // Zooms the camera in by a single increment.
  void zoomIn();

  // Raises the camera into the air.
  void liftCam();
  
  // Lowers the camera towards the water.
  void dropCam();

  // Draws the scene.
  void render();

 private:
  // Root of the scene graph where all rendering begins.
  SceneNode* sceneGraphRoot_;
  // Pointer to the camera node in the scene graph. The graph itself is
  // responsible for freeing the camera, so we don't use this pointer for
  // ownership, but we can't make it const either because we need to mutate the
  // camera, hence the naked pointer.
  CameraNode* camera_;

  DISALLOW_EVIL_CONSTRUCTORS(Scene);
};

#endif

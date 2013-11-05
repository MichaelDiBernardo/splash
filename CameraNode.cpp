#include "CameraNode.h"
#include <math.h>
#include <iostream>
using std::cerr;
using std::endl;
#include "Config.h"
#include "DinoNode.h"
#include "Orientation.h"

CameraNode::CameraNode(const string& id, const DinoNode& target)
  : SceneNode(id), focus_(target) {
  followDistance_ = Config::DEFAULT_CAMERA_FOLLOW_DISTANCE;
  camH_ = Config::DEFAULT_CAMERA_HEIGHT;
}

CameraNode::~CameraNode() {
}

void CameraNode::zoomIn() {
  followDistance_ -= Config::CAMERA_ZOOM_INCREMENT;

  if (followDistance_ < Config::MIN_CAMERA_DISTANCE)
    followDistance_ = Config::MIN_CAMERA_DISTANCE;
}

void CameraNode::zoomOut() {
  followDistance_ += Config::CAMERA_ZOOM_INCREMENT;

  if (followDistance_ > Config::MAX_CAMERA_DISTANCE)
    followDistance_ = Config::MAX_CAMERA_DISTANCE;
}

void CameraNode::raise() {
  camH_ += Config::CAMERA_HEIGHT_INCREMENT;

  if (camH_ > Config::MAX_CAMERA_HEIGHT)
    camH_ = Config::MAX_CAMERA_HEIGHT;
}

void CameraNode::lower() {
  camH_ -= Config::CAMERA_HEIGHT_INCREMENT;

  if (camH_ < Config::MIN_CAMERA_HEIGHT)
    camH_ = Config::MIN_CAMERA_HEIGHT;
}

void CameraNode::render() {
  glPushMatrix();

  // Position camera first.
  const Orientation& o = focus_.getOrientation();

  double cameraX = o.getX() - followDistance_ * cos(o.getAngle());
  double cameraZ = o.getY() - followDistance_ * sin(o.getAngle());
  double cameraY = camH_;

  gluLookAt(cameraX, cameraY, cameraZ, o.getX(), 0, o.getY(), 0, 1, 0);
  #ifdef __debug
  cerr << "Camera at: " << cameraX << " " << cameraY << " " << cameraZ 
       << " looking at " << o.getX() << " 0 " << o.getY() << endl;
  #endif

  // Now bot out rest of scene graph.
  SceneNode::render();
  glPopMatrix();
}

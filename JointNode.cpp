#include "JointNode.h"
#include <assert.h>
#include "os.h"

JointNode::JointNode(const string& id, double xToJoint, double yToJoint, double zToJoint,
                     double xFromJoint, double yFromJoint, double zFromJoint) 
  : SceneNode(id) {
  angle_[(int)ABOUT_X] = 0.0;
  angle_[(int)ABOUT_Y] = 0.0;
  angle_[(int)ABOUT_Z] = 0.0;

  displacementFromParent_[0] = xToJoint;
  displacementFromParent_[1] = yToJoint;
  displacementFromParent_[2] = zToJoint;

  displacementToChild_[0] = xFromJoint;
  displacementToChild_[1] = yFromJoint;
  displacementToChild_[2] = zFromJoint;
}

JointNode::~JointNode() {
}

void JointNode::bend(double a, MotionType direction) {
  angle_[(int)direction] = a;
}

void JointNode::straighten() {
  angle_[0] = 0;
  angle_[1] = 0;
  angle_[2] = 0;
}

void JointNode::render() {
  glPushMatrix();
  glTranslated(displacementFromParent_[0], displacementFromParent_[1], displacementFromParent_[2]);
  glRotated(angle_[(int)ABOUT_X], 1.0, 0.0, 0.0);
  glRotated(angle_[(int)ABOUT_Y], 0.0, 1.0, 0.0);
  glRotated(angle_[(int)ABOUT_Z], 0.0, 0.0, 1.0);
  glTranslated(displacementToChild_[0], displacementToChild_[1], displacementToChild_[2]);
  SceneNode::render();

  glPopMatrix();
}

void JointNode::addChild(SceneNode* child) {
  assert(SceneNode::getNumChildren() < 2);
  SceneNode::addChild(child);
}

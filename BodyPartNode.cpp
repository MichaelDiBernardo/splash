#include "BodyPartNode.h"
#include "os.h"
#include "ColorSpec.h"
using namespace std;

BodyPartNode::BodyPartNode(const string& id, double xRadius, double yRadius, double zRadius, const ColorSpec* c)
             :SceneNode(id), xrad_(xRadius), yrad_(yRadius), zrad_(zRadius), myC_(c) {
}

BodyPartNode::~BodyPartNode() {
}

void BodyPartNode::render() {
  glPushMatrix();
  myC_->set();
  glScaled(xrad_, yrad_, zrad_);
  #ifdef __debug
  glutWireSphere(1, NUM_SLICES, NUM_STACKS);
  #else
  glutSolidSphere(1, NUM_SLICES, NUM_STACKS);
  #endif
  glPopMatrix();
  SceneNode::render();
}

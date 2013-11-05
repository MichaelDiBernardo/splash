#include "SpikeNode.h"
#include "os.h"
#include "ColorSpec.h"

SpikeNode::SpikeNode(const string& id, double myBase, double myHeight, SpikeOrientation myO, const ColorSpec* c)
  : SceneNode(id), base_(myBase), height_(myHeight), o_(myO), myC_(c) {
}

SpikeNode::~SpikeNode() {
}

void initRotationAmounts(SpikeOrientation o, double* xAmount, double* yAmount) {
  if (o == SPIKE_VERTICAL) {
    *xAmount = 270;
    *yAmount = 0;
  }
  else if (o == SPIKE_HORIZONTAL) {
    *xAmount = 0;
    *yAmount = 90;
  }
  else if (o == SPIKE_DIAG_LEFT) {
    *xAmount = -30;
    *yAmount = 45;
  }
  else {
    *xAmount = -150;
    *yAmount = 45;
  }
}

void SpikeNode::render() {
  double xRotationAmount, yRotationAmount;
  initRotationAmounts(o_, &xRotationAmount, &yRotationAmount);

  glPushMatrix();
  myC_->set();
  glRotated(xRotationAmount, 1, 0, 0);
  glRotated(yRotationAmount, 0, 1, 0);
  #ifdef __debug
  glutWireCone(base_, height_, NUM_SLICES, NUM_STACKS);
  #else
  glutSolidCone(base_, height_, NUM_SLICES, NUM_STACKS);
  #endif
  glPopMatrix();
  
  SceneNode::render();
}

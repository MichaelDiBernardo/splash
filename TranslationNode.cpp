#include "TranslationNode.h"
#include "os.h"

TranslationNode::TranslationNode(const string& id, double xDisplacement, double yDisplacement, double zDisplacement)
             :SceneNode(id), xdis_(xDisplacement), ydis_(yDisplacement), zdis_(zDisplacement) {
}

TranslationNode::~TranslationNode() {
}

void TranslationNode::setTranslation(double xDisplacement, double yDisplacement, double zDisplacement) {
  xdis_ = xDisplacement;
  ydis_ = yDisplacement;
  zdis_ = zDisplacement;
}

double TranslationNode::getX() const {
  return xdis_;
}

double TranslationNode::getY() const {
  return ydis_;
}

double TranslationNode::getZ() const {
  return zdis_;
}

void TranslationNode::render() {
  glPushMatrix();
    
  // Perform the translation.
  glTranslated(xdis_, ydis_, zdis_);

  // Update all of my children.
  SceneNode::render();
  
  glPopMatrix();
}

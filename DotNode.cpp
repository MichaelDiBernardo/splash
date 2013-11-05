#include "DotNode.h"
#include "os.h"
#include "ColorSpec.h"
#include "Config.h"
#include "PropSpec.h"

DotNode::DotNode(const string& id, const PropSpec& initSpec) 
  : PropNode(id, initSpec) {
  delta_h_ = 0;
  delta_hv_ = Config::DOT_DIM/10;
  myDList_ = glGenLists(1);

  glNewList(myDList_, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);

    glMaterialfv(GL_FRONT, GL_AMBIENT, Config::SHINY_MAT_AMB);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Config::SHINY_MAT_AMB);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Config::SHINY_MAT_SPEC);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    Config::DOT_COLOR->set();
    glutSolidSphere(Config::DOT_DIM, 20, 20);

    glPopAttrib();
    glPopMatrix();
  glEndList();
}

DotNode::~DotNode() {
}

void DotNode::render() {
  if (myProp_.isActive()) {
    // compute delta_h_
    if (delta_h_ > 0)
      delta_hv_ -= Config::DOT_DIM/60;
    else
      delta_hv_ += Config::DOT_DIM/60;

    delta_h_ += delta_hv_;

    glPushMatrix();
    glTranslated(myProp_.getXPos(), Config::DOT_CENTER_HEIGHT + delta_h_, myProp_.getYPos());

    glCallList(myDList_);
    glPopMatrix();
  }
}

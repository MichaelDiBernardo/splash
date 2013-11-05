#include "ObjNode.h"
#include <assert.h>
#include "os.h"
#include "ColorSpec.h"
#include "Config.h"
#include "PropSpec.h"
#include "objreader.h"

ObjNode::ObjNode(const string& id, const PropSpec& initSpec) 
  : PropNode(id, initSpec) {
  objReader o;
  double scaleHeight = 1.0;
  double liftHeight = 0.0;
  double scaleDimension = 1.0;
  
  const ColorSpec* c;

  if (initSpec.getType() == TORCH_PROP) {
    o.loadObj(Config::TORCH_OBJ_FILE);
    scaleHeight = 1.5;
    liftHeight = 0.0;
    c = Config::TORCH_COLOR;
  }
  else if (initSpec.getType() == THRONE_PROP) {
    o.loadObj(Config::THRONE_OBJ_FILE);
    scaleHeight = 1.5;
    liftHeight = 0.5;
    c = Config::THRONE_COLOR;
  }
  else if (initSpec.getType() == TROPHY_PROP) {    
    o.loadObj(Config::TROPHY_OBJ_FILE);
    scaleHeight = 1.0;
    liftHeight = 1;
    // Minor hack
    scaleDimension *= 2.8;
    c = Config::TROPHY_COLOR;
  }
  else {
    assert(false);
  }
  
  myList_ = glGenLists(1);
  
  o.centerObject();
  glNewList(myList_, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    c -> set();
    glMaterialfv(GL_FRONT, GL_AMBIENT, Config::SHINY_MAT_AMB);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Config::SHINY_MAT_DIF);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Config::SHINY_MAT_SPEC);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glTranslated(myProp_.getXPos(), liftHeight, myProp_.getYPos());
    o.resizeObject();
    glScaled(scaleDimension * myProp_.getXDim(), scaleHeight, scaleDimension * myProp_.getYDim());
    o.displayObj();
    glPopAttrib();
    glPopMatrix();
  glEndList();
}

ObjNode::~ObjNode() {
}

void ObjNode::render() {
  glCallList(myList_);
  SceneNode::render();
}

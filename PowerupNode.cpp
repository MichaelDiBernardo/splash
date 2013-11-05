#include "PowerupNode.h"
#include "os.h"
#include "ColorSpec.h"
#include "Config.h"
#include "PropSpec.h"

PowerupNode::PowerupNode(const string& id, GLenum lightIndex, const PropSpec& initSpec)
  : PropNode(id, initSpec), myRot_(0), myLight_(lightIndex) {
  glEnable(myLight_);
}

PowerupNode::~PowerupNode() {
}

void PowerupNode::render() {
  if (!myProp_.isActive()) {
    glDisable(myLight_);
    return;
  }

  myRot_ += 4;
  if (myRot_ > 360) myRot_ = 0;

  glPushMatrix();

  GLfloat mat_emission[4]; 
  for (int i = 0; i < 4; ++i)  mat_emission[i] = 0.0;

  // A little hacky, but not horrific...
  if (myProp_.getType() == FEAR_POWERUP_PROP) {
    Config::FEAR_POWERUP_COLOR->set();
    glLightfv(myLight_, GL_AMBIENT, Config::FEAR_POWERUP_AMB);
    glLightfv(myLight_, GL_DIFFUSE, Config::FEAR_POWERUP_DIF);
    glLightfv(myLight_, GL_SPECULAR, Config::FEAR_POWERUP_SPEC);
    mat_emission[0] = 0.9;
  }
  else if (myProp_.getType() == FREEZE_POWERUP_PROP) {
    Config::FREEZE_POWERUP_COLOR->set();
    glLightfv(myLight_, GL_AMBIENT, Config::FREEZE_POWERUP_AMB);
    glLightfv(myLight_, GL_DIFFUSE, Config::FREEZE_POWERUP_DIF);
    glLightfv(myLight_, GL_SPECULAR, Config::FREEZE_POWERUP_SPEC);
    mat_emission[2] = 0.9;
  }
  else {
    Config::SPEED_POWERUP_COLOR->set();
    glLightfv(myLight_, GL_AMBIENT, Config::SPEED_POWERUP_AMB);
    glLightfv(myLight_, GL_DIFFUSE, Config::SPEED_POWERUP_DIF);
    glLightfv(myLight_, GL_SPECULAR, Config::SPEED_POWERUP_SPEC);
    mat_emission[1] = 0.9;
  }

  GLfloat myPos_[4];
  myPos_[0] = myProp_.getXPos(); myPos_[1] = Config::POWERUP_CENTER_HEIGHT; myPos_[2] = myProp_.getYPos(); myPos_[3] = 1;
  glLightfv(myLight_, GL_POSITION, myPos_);
  glLightf(myLight_, GL_CONSTANT_ATTENUATION, 0.1);
  glLightf(myLight_, GL_QUADRATIC_ATTENUATION, 0.1);
      
  glPushAttrib(GL_LIGHTING_BIT);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, Config::SHINY_MAT_AMB);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Config::SHINY_MAT_AMB);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Config::SHINY_MAT_SPEC);
  glMaterialf(GL_FRONT, GL_SHININESS, 75);
  glTranslated(myProp_.getXPos(), Config::POWERUP_CENTER_HEIGHT, myProp_.getYPos());
  
  glRotated(myRot_, 0, 1, 0);
  glPushMatrix();
  glRotated(90, 1, 0, 0);
  glutSolidCone(Config::POWERUP_DIM, 2 * Config::POWERUP_DIM, 4, 1);
  glPopMatrix();
  glPushMatrix();
  glRotated(-90, 1, 0, 0);
  glutSolidCone(Config::POWERUP_DIM, 2 * Config::POWERUP_DIM, 4, 1);
  glPopMatrix();
  glPopAttrib();

  glPopMatrix();
  SceneNode::render();
}

#include "IslandNode.h"
#include "os.h"
#include "PropSpec.h"
#include "Config.h"

IslandNode::IslandNode(const string& id, GLuint myTex_, const PropSpec& initSpec)
  : PropNode(id, initSpec), myTex_(myTex_) {
  height_ = -1 * Config::OCEAN_FLOOR_DEPTH + Config::ISLAND_HEIGHT_ABOVE_WATER;

  myQuadProperties_ = gluNewQuadric();
  gluQuadricTexture(myQuadProperties_, true);
  gluQuadricDrawStyle(myQuadProperties_, GLU_FILL);
}

IslandNode::~IslandNode() {
  gluDeleteQuadric(myQuadProperties_);
}

void IslandNode::render() {
  glPushMatrix();
  glPushAttrib(GL_LIGHTING_BIT);
  glPushAttrib(GL_TEXTURE_BIT);

  glMaterialfv(GL_FRONT, GL_AMBIENT, Config::SHINY_MAT_AMB);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Config::SHINY_MAT_DIF);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Config::SHINY_MAT_AMB);
  glMaterialf(GL_FRONT, GL_SHININESS, 10);

  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, myTex_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glColor3f(0.2, 0.2, 0.2);
  glTranslated(myProp_.getXPos(), Config::OCEAN_FLOOR_DEPTH, myProp_.getYPos());
  glScaled(myProp_.getXDim(), height_, myProp_.getYDim());
  //glutSolidSphere(1, 20, 20);
  gluSphere(myQuadProperties_, 1, 20, 20);

  SceneNode::render();

  glPopAttrib();
  glPopAttrib();
  glPopMatrix();
}

#include "EnvironmentalLightNode.h"
#include "os.h"
#include "Config.h"

EnvironmentalLightNode::EnvironmentalLightNode(const string& id, double x, double y)
  : SceneNode(id), myX_(x), myY_(y) {
  glEnable(GL_LIGHT0);
}

EnvironmentalLightNode::~EnvironmentalLightNode() {
}

void EnvironmentalLightNode::render() {
  glLightfv(GL_LIGHT0, GL_AMBIENT, Config::SUNLIGHT_AMB);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Config::SUNLIGHT_DIF);
  glLightfv(GL_LIGHT0, GL_SPECULAR, Config::SUNLIGHT_SPEC);
  
  GLfloat myPos[4];
  myPos[0] = myX_; myPos[1] = 100; myPos[2] = myY_; myPos[3] = 0;
  
  glLightfv(GL_LIGHT0, GL_POSITION, myPos);
  
  SceneNode::render();
}

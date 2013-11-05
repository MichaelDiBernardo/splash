#include "SettingNode.h"
#include "os.h"
#include "ColorSpec.h"
#include "Config.h"
#include "readtex.h"

SettingNode::SettingNode(const string& id, double worldWidth, double
                         worldHeight, GLuint floorTexInd, GLuint skyTexInd)     
  : SceneNode(id), width_(worldWidth), height_(worldHeight), floorInd_(floorTexInd), 
    skyInd_(skyTexInd) {
}

SettingNode::~SettingNode() {
}

void SettingNode::render() {
  glPushMatrix();
  glPushAttrib(GL_TEXTURE_BIT);
  glPushAttrib(GL_LIGHTING_BIT);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, floorInd_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  double rpt = 16 * width_;
  
  glBegin(GL_QUADS);    
    Config::OCEAN_FLOOR_COLOR->set();
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(-100, Config::OCEAN_FLOOR_DEPTH, -100);
    glTexCoord2f(0.0, rpt);
    glVertex3d(-100, Config::OCEAN_FLOOR_DEPTH, 100);
    glTexCoord2f(rpt, rpt);
    glVertex3d(100, Config::OCEAN_FLOOR_DEPTH, 100);
    glTexCoord2f(rpt, 0.0);
    glVertex3d(100, Config::OCEAN_FLOOR_DEPTH, -100);
  glEnd();
  
  glBegin(GL_QUADS);    
    glDisable(GL_DEPTH_TEST);
    Config::OCEAN_WATER_COLOR->set();
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(-100, 0, -100);
    glVertex3d(-100, 0, 100);
    glVertex3d(100, 0, 100);
    glVertex3d(100, 0, -100);
    glEnable(GL_DEPTH_TEST);
  glEnd();

  glPopAttrib();
  glPopAttrib();
  glPopMatrix();
}

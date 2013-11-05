#include "BoxNode.h"
#include <math.h>
#include "os.h"
#include "ColorSpec.h"
#include "Config.h"
#include "PropSpec.h"

BoxNode::BoxNode(const string& id, GLuint mt, const PropSpec& initSpec)
  : PropNode(id, initSpec), myTex_(mt) {
}

BoxNode::~BoxNode() {
}

void BoxNode::render() {
  glPushMatrix();
  glPushAttrib(GL_TEXTURE_BIT);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, myTex_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Config::SHINY_MAT_DIF);
  
  Config::BOX_COLOR->set();
  glTranslated(myProp_.getXPos(), 0, myProp_.getYPos());
  glScaled(myProp_.getXDim(), Config::BOX_HEIGHT, myProp_.getYDim());
  
  glBegin(GL_QUADS);
    glNormal3d(1, 0, 0);
    glTexCoord2f(0, 0);        
    glVertex3d(0.5, -0.5, -0.5); 
    glTexCoord2f(round(myProp_.getYDim()), 0);        
    glVertex3d(0.5, -0.5, 0.5); 
    glTexCoord2f(round(myProp_.getYDim()), Config::BOX_HEIGHT);        
    glVertex3d(0.5, 0.5, 0.5); 
    glTexCoord2f(0, Config::BOX_HEIGHT);        
    glVertex3d(0.5, 0.5, -0.5); 

    glNormal3d(-1, 0, 0);
    glTexCoord2f(0, 0);        
    glVertex3d(-0.5, -0.5, -0.5); 
    glTexCoord2f(round(myProp_.getYDim()), 0);        
    glVertex3d(-0.5, -0.5, 0.5); 
    glTexCoord2f(round(myProp_.getYDim()), Config::BOX_HEIGHT);        
    glVertex3d(-0.5, 0.5, 0.5); 
    glTexCoord2f(0, Config::BOX_HEIGHT);        
    glVertex3d(-0.5, 0.5, -0.5); 
    
    glNormal3d(0, 1, 0);
    glTexCoord2f(0, 0);        
    glVertex3d(-0.5, 0.5, -0.5); 
    glTexCoord2f(round(myProp_.getXDim()), 0);        
    glVertex3d(0.5, 0.5, -0.5); 
    glTexCoord2f(round(myProp_.getXDim()), round(myProp_.getYDim()));        
    glVertex3d(0.5, 0.5, 0.5); 
    glTexCoord2f(0, round(myProp_.getYDim()));        
    glVertex3d(-0.5, 0.5, 0.5); 
    
    glNormal3d(0, -1, 0);
    glTexCoord2f(0, 0);        
    glVertex3d(-0.5, -0.5, -0.5); 
    glTexCoord2f(round(myProp_.getXDim()), 0);        
    glVertex3d(-0.5, -0.5, 0.5); 
    glTexCoord2f(round(myProp_.getXDim()), round(myProp_.getYDim()));        
    glVertex3d(0.5, -0.5, 0.5); 
    glTexCoord2f(0, round(myProp_.getYDim()));        
    glVertex3d(0.5, -0.5, -0.5); 

    glNormal3d(0, 0, 1);
    glTexCoord2f(0, 0);        
    glVertex3d(-0.5, -0.5, 0.5); 
    glTexCoord2f(round(myProp_.getXDim()), 0);        
    glVertex3d(0.5, -0.5, 0.5); 
    glTexCoord2f(round(myProp_.getXDim()), Config::BOX_HEIGHT);        
    glVertex3d(0.5, 0.5, 0.5); 
    glTexCoord2f(0, Config::BOX_HEIGHT);        
    glVertex3d(-0.5, 0.5, 0.5); 
    
    glNormal3d(0, 0, -1);
    glTexCoord2f(0, 0);        
    glVertex3d(-0.5, -0.5, -0.5); 
    glTexCoord2f(round(myProp_.getXDim()), 0);        
    glVertex3d(0.5, -0.5, -0.5); 
    glTexCoord2f(round(myProp_.getXDim()), Config::BOX_HEIGHT);        
    glVertex3d(0.5, 0.5, -0.5); 
    glTexCoord2f(0, Config::BOX_HEIGHT);        
    glVertex3d(-0.5, 0.5, -0.5); 
  glEnd();
  
  SceneNode::render();
  glPopAttrib();
  glPopMatrix();
}

// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class 2DUtils and related constructs.
#include "Utils2D.h"
#include <math.h>
#include "os.h"

void Utils2D::drawCircle(double radius, int slices) {
  glBegin(GL_POLYGON);
  for (double t = 0; t <= 2*M_PI; t+= M_PI/slices) 
    glVertex2d(radius * cos(t), radius * sin(t));
  glEnd();
}

void Utils2D::drawString(const string& s) {
  for (unsigned int i = 0; i < s.length(); ++i) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
  }
}

void Utils2D::drawString(const string& s, double x, double y) {
  glPushMatrix();
  glTranslated(x, y, 0.0);
  Utils2D::drawString(s);
  glPopMatrix();
}

void Utils2D::drawShinyBall(double radius) {
  drawCircle(radius, 20);
  glTranslatef(-radius/3, 2.0/15.0 * radius, 0);
  glColor3f(0.8, 0.8, 0.8);
  drawCircle(2.0/15.0 * radius, 5);
}

Utils2D::Utils2D() {
}

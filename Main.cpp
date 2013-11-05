// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// 
// Driver program that switches between renderers as necessary to transition
// between game states.

#include <assert.h>
#include <math.h>
#include <iostream>
using std::cout; using std::endl;
#include "Config.h"
#include "EndgameRenderer.h"
#include "Engine.h"
#include "FadeRenderer.h"
#include "GameplayRenderer.h"
#include "MenuRenderer.h"
#include "Renderer.h"
#include "SplashscreenRenderer.h"
#include "WinscreenRenderer.h"

void switchTo(Renderer* r);
void fade(int before, int duration, NextAction doneAction);

Renderer* current;
int w;
int h;

// Used to govern the frame rate of the game.
void timedCallback(int value) {
  glutPostRedisplay();
}

// Display callback. Directs the scene graph to draw
// the scene.
void display(void) {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  NextAction action = current->render();
  
  glutSwapBuffers();

  if (action == RA_REDISPLAY) {
    glutTimerFunc( lround((1.0/Config::FRAME_RATE) * 1000), timedCallback, 0);
  } else if (action == RA_TITLE_TO_FADE) {
    fade(0, 1, RA_FADE_TO_MENU);
  } else if (action == RA_MENU_TO_FADE) {
    fade(0, 1, RA_FADE_TO_GAME);
  } else if (action == RA_FADE_TO_GAME) {
    FadeRenderer* fader = static_cast<FadeRenderer*>(current);
    const MenuRenderer& menu = static_cast<const MenuRenderer&>(fader->getRenderer());
    int nextLevel = menu.levelPicked();
    switchTo(new GameplayRenderer(nextLevel));
  } else if (action == RA_FADE_TO_WINSCREEN) {
    FadeRenderer* fader = static_cast<FadeRenderer*>(current);
    const GameplayRenderer& g = static_cast<const GameplayRenderer&>(fader->getRenderer());
    switchTo(new WinscreenRenderer(g.getWinInfo()));
  } else if (action == RA_FADE_TO_MENU) {
    switchTo(new MenuRenderer());
  } else if (action == RA_GAME_LOST_TO_FADE) {
    fade(5, 1, RA_FADE_TO_MENU);
  } else if (action == RA_GAME_WON_TO_FADE) {
    fade(5, 1, RA_FADE_TO_WINSCREEN);
  } else if (action == RA_WINSCREEN_TO_FADE) {
    const WinscreenRenderer* win = static_cast<const WinscreenRenderer*>(current);
    if (win->showEndScreen()) {
      fade(0, 1, RA_FADE_TO_END);
    } else {
      fade(0, 1, RA_FADE_TO_MENU);
    }
  } else if (action == RA_FADE_TO_END) {
    switchTo(new EndgameRenderer());
  } else if (action == RA_END_TO_FADE) {
    fade(0, 1, RA_FADE_TO_MENU);
  }
  else {
    assert(false);
  }
}

// Called when 'normal' keys are hit.
void onKeyDown(unsigned char key, int x, int y) {
  if (static_cast<int>(key) == 27) {
    cout << "Thanks for playing." << endl;
    exit(0);
  }
  else if (current->isEnabled()) 
    current->onKeyDown(key, x, y);
}

void onKeyUp(unsigned char key, int x, int y) {
  if (current->isEnabled())
    current->onKeyUp(key, x, y);
}

// Called when 'special' keys are hit.
void onSpecialKeyDown(int key, int x, int y) {
  if (current->isEnabled())
    current->onSpecialKeyDown(key, x, y);
}

// Called when special keys are released.
void onSpecialKeyUp(int key, int x, int y) {
  if (current->isEnabled())
    current->onSpecialKeyUp(key, x, y);
}

// Fixes things when the window gets resized.
void myReshape(int width, int height) {
  w = width;
  h = height;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  current->reshape(w, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void switchTo(Renderer* r) {
  r->init();
  Renderer* old = current;
  current = r;
  glutIgnoreKeyRepeat(current->shouldKeysRepeat());
  myReshape(w, h);
  glutPostRedisplay();

  delete old;
}

void fade(int before, int duration, NextAction doneAction) {
  FadeRenderer* fader = new FadeRenderer(before, duration, doneAction, current);
  fader->init();
  current = fader;
  myReshape(w, h);
  glutPostRedisplay();
}

// Starts the main event loop.
int main(int argc, char **argv) {
  // wake up glut
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Set window size
  glutInitWindowSize(Config::DEFAULT_SCREEN_WIDTH, Config::DEFAULT_SCREEN_HEIGHT);
  glutCreateWindow("Splash!");

  switchTo(new SplashscreenRenderer());
  /*
  WinRecord* win_ = new WinRecord;
  win_->oldTimes.push_back(30000);
  win_->oldTimes.push_back(60000);
  win_->oldTimes.push_back(90000);
  win_->oldTimes.push_back(120000);
  win_->oldTimes.push_back(150000);
  win_->newTime = 45000;
  win_->par = 60;
  win_->level = 1;
  win_->unlockedNextLevel = true;
  switchTo(new WinscreenRenderer(win_));
  */

  // register callbacks
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(onKeyDown);
  glutKeyboardUpFunc(onKeyUp);
  glutSpecialFunc(onSpecialKeyDown);
  glutSpecialUpFunc(onSpecialKeyUp);

  // Go go go!
  glutMainLoop();
  return 0;
}

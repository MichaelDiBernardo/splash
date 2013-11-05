// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Encapsulates the view/controller functions that are registered as callbacks
// with GLUT. For simplicity, we don't seperate the view and controller logic.
//
// The default renderer provides stubs for all implemented methods: That is,
// all of them do essentially nothing.
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Basics.h"

enum NextAction {
  RA_NONE,
  RA_REDISPLAY,
  RA_TITLE_TO_FADE,
  RA_MENU_TO_FADE,
  RA_FADE_TO_GAME,
  RA_FADE_TO_MENU,
  RA_FADE_TO_WINSCREEN,
  RA_GAME_WON_TO_FADE,
  RA_GAME_LOST_TO_FADE,
  RA_WINSCREEN_TO_FADE,
  RA_FADE_TO_END,
  RA_END_TO_FADE
};

class Renderer {
 public:

  // Create a new renderer.
  Renderer();

  // Free resources used by this renderer.
  virtual ~Renderer();

  // Init your rendering environment (i.e. set/enable gl configuration bits).
  virtual void init();

  // Render your scene. Before this is called, color and buffer bits will be
  // cleared and the matrix mode will be switched to GL_MODELVIEW, with an
  // identity matrix loaded.
  virtual NextAction render();

  // Change projection matrix to deal with new reshaping. Before this is
  // called, the viewport is set to the new width and height, the matrix mode
  // is switched to GL_PROJECTION, and the identity matrix is loaded. After it
  // is called, the matrix mode is switched back to GL_MODELVIEW, and the
  // identity matrix is loaded.
  virtual void reshape(int newWidth, int newHeight);

  // Intercept normal key down events. See 'man glutKeyboardFunc' for details.
  virtual void onKeyDown(unsigned char key, int x, int y);

  // Intercept normal key up events. See 'man glutKeyboardUpFunc' for details.
  virtual void onKeyUp(unsigned char key, int x, int y);

  // Intercept special key down events. See 'man glutSpecialFunc' for details.
  virtual void onSpecialKeyDown(int key, int x, int y);

  // Intercept special key up events. See 'man glutSpecialUpFunc' for details.
  virtual void onSpecialKeyUp(int key, int x, int y);

  // Should we allow keys to repeat or not?
  virtual bool shouldKeysRepeat() const;

  // Stop listening to inputs.
  void disable();

  // Start listening to inputs.
  void enable();

  // Is this renderer listening to inputs?
  bool isEnabled() const;
  
 private:
  // Is this renderer listening to inputs?
  bool enabled_;

  DISALLOW_EVIL_CONSTRUCTORS(Renderer);
};

#endif

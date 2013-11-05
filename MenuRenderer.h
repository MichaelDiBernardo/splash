// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Renders the menu from which the user selects which level to play.
#ifndef __MENURENDERER_H__
#define __MENURENDERER_H__

#include <vector>
using std::vector;
#include "Basics.h"
#include "TexturedScreenRenderer.h"

class Level;
class Timer;

class MenuRenderer : public TexturedScreenRenderer {
 public:
  // Create a new menu renderer.
  MenuRenderer();
  // Free resources used by this renderer.
  ~MenuRenderer();

  // Respond to user inputs.
  virtual void onKeyDown(unsigned char key, int x, int y);

  virtual void onSpecialKeyDown(int key, int x, int y);

  virtual bool shouldKeysRepeat() const;

  // After the user has selected a level, this will return the number of the
  // level they picked.
  int levelPicked() const;

 protected:
  // What to render over the image background.
  NextAction renderOverBackground();

 private:
  // What level is the user currently looking at?
  int currentSelectedLevel_;
  // How many levels have been unlocked thus far?
  int numLevelsUnlocked_;
  // Level data.
  vector<Level*> levels_;
  // Has the user hit 'enter' or an equivalent key yet?
  bool picked_;

  // Is the current selected level locked?
  bool locked() const;

  DISALLOW_EVIL_CONSTRUCTORS(MenuRenderer);
};

#endif

// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Renders the level summary that comes up after the player clears a level.
// This is a horrible named class, but it seemed like a good idea at the
// time...
#ifndef __WINSCREENRENDERER_H__
#define __WINSCREENRENDERER_H__

#include "Renderer.h"

struct WinRecord;

class WinscreenRenderer : public Renderer {
 public:
  // Takes ownership of given WinRecord.
  WinscreenRenderer(WinRecord* win);

  // Free resources used by this renderer.
  ~WinscreenRenderer();

  virtual void init();

  virtual NextAction render();

  virtual void reshape(int newWidth, int newHeight);

  virtual void onKeyDown(unsigned char key, int x, int y);

  bool shouldKeysRepeat() const;

  bool showEndScreen() const;

 private:
  // WinRecord to be displayed by this renderer.
  WinRecord* win_;
  // Ready to turn over?
  bool switch_;
};

#endif

// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Renderer to display end-of-game screen.
#ifndef __ENDGAMERENDERER_H__
#define __ENDGAMERENDERER_H__

#include "Basics.h"
#include "TexturedScreenRenderer.h"

class EndgameRenderer : public TexturedScreenRenderer {
 public:
  EndgameRenderer();
  ~EndgameRenderer();

  virtual void onKeyDown(unsigned char key, int x, int y);

  virtual bool shouldKeysRepeat() const;

 protected:
  // What to render over the image background.
  NextAction renderOverBackground();

 private:
  bool switch_;

  DISALLOW_EVIL_CONSTRUCTORS(EndgameRenderer);
};

#endif

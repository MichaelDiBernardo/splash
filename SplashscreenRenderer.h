// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Renders the title/splash screen at game launch.
#ifndef __SPLASHSCREENRENDERER_H__
#define __SPLASHSCREENRENDERER_H__

#include "Basics.h"
#include "TexturedScreenRenderer.h"
#include "os.h"

class Timer;

class SplashscreenRenderer : public TexturedScreenRenderer {
 public:
  // New SplashscreenRenderer.
  SplashscreenRenderer();
  
  // Free resources used by this renderer.
  ~SplashscreenRenderer();

  // Allows user to 'hit any key' when prompted.
  virtual void onKeyDown(unsigned char key, int x, int y);

  virtual bool shouldKeysRepeat() const;

 protected:
  // Does the post-texture rendering.
  NextAction renderOverBackground();

 private:
  // Times how long to wait before allowing keypress to progress.
  Timer* pauser_;
  // Is it time to turn over?
  bool switch_;

  DISALLOW_EVIL_CONSTRUCTORS(SplashscreenRenderer);
};

#endif

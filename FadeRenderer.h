// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Given a renderer, fades out the rendered scene gradually.
#ifndef __FADE_RENDERER_H__
#define __FADE_RENDERER_H__

#include "Basics.h"
#include "Renderer.h"
class Timer;

class FadeRenderer : public Renderer {
 public:

  // Create a new renderer. Takes ownership of sceneToFade. 'doneAction'
  // describes the NextAction that should be returned when this fader is done
  // fading.
  FadeRenderer(int secondsToFade, NextAction doneAction, Renderer* sceneToFade);

  // Same as above but waits for 'secondsBeforeFade' seconds before starting
  // the fading.
  FadeRenderer(int secondsBeforeFade, int secondsToFade, NextAction doneAction, Renderer* sceneToFade);

  // Free resources used by this renderer.
  virtual ~FadeRenderer();

  virtual void init();

  // Renders the scene given at construction time, and then renders a black
  // faded mask above it.
  virtual NextAction render();

  // Subsequent overridden methods simply forward calls onto the scene to fade.
  virtual void reshape(int newWidth, int newHeight);

  virtual void onKeyDown(unsigned char key, int x, int y);

  virtual void onKeyUp(unsigned char key, int x, int y);

  virtual void onSpecialKeyDown(int key, int x, int y);

  virtual void onSpecialKeyUp(int key, int x, int y);

  virtual bool shouldKeysRepeat() const;

  // Get the renderer maintained by this fader.
  const Renderer& getRenderer() const;
  
 private:
  // How long should we wait before we start fading?
  int durationBefore_;
  // How long should we fade for?
  int duration_;
  // What result should we return when fading is done?
  NextAction doneAction_;
  // Scene to fade out.
  Renderer* target_;
  // Ticks off time spent fading.
  Timer* fadeTimer_;
  
  DISALLOW_EVIL_CONSTRUCTORS(FadeRenderer);
};

#endif

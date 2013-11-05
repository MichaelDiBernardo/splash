// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Renders a screen that has an image as the background. If you want to render
// other stuff after that overtop of the texture, override the protected method
// "renderOverBackground".
#ifndef __TEXTUREDSCREENRENDERER_H__
#define __TEXTUREDSCREENRENDERER_H__

#include "Basics.h"
#include "Renderer.h"
#include "os.h"

class TexturedScreenRenderer : public Renderer {
 public:
  // Creates a renderer that will render the screen using the image with the
  // given filename. Images must be .sgi format, and must have dimensions that
  // are a power of 2 (e.g. 32x32, 128x128, 512x512). 
  explicit TexturedScreenRenderer(const char* filename);

  // Frees resources used by this renderer.
  virtual ~TexturedScreenRenderer();

  virtual void init();

  virtual void reshape(int newWidth, int newHeight);

  // Renders the background image and then calls renderOverBackground. Returns
  // the NextAction returned by renderOverBackground.
  virtual NextAction render();
  
 protected:
  // Does nothing, returns RA_REDISPLAY. Override this to make it do something
  // useful.
  virtual NextAction renderOverBackground();

 private:
  // Texture index of the texture to render on the background.
  GLuint ssTexName_[1];

  DISALLOW_EVIL_CONSTRUCTORS(TexturedScreenRenderer);
};

#endif

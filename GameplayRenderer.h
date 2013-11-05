// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Renderer for the main game.
#ifndef __GAMEPLAYRENDERER_H__
#define __GAMEPLAYRENDERER_H__

#include "Basics.h"
#include "Renderer.h"

class Engine;
class EngineInput;
class Scene;
class Timer;
struct WinRecord;

class GameplayRenderer : public Renderer {
 public:
  // Create a renderer for the given level. This will construct the engine to
  // play that level and start the game.
  explicit GameplayRenderer(int level);

  // Free resources used by this renderer.
  ~GameplayRenderer();

  virtual void init();

  // Render the scene and evolve the model by one timestep.
  virtual NextAction render();

  virtual void reshape(int newWidth, int newHeight);

  // Receive control input from user.
  virtual void onKeyDown(unsigned char key, int x, int y);

  virtual void onSpecialKeyDown(int key, int x, int y);

  virtual void onSpecialKeyUp(int key, int x, int y);

  virtual bool shouldKeysRepeat() const;

  // After the game is over, this will return a record of the player's win if
  // they won, or NULL otherwise.
  WinRecord* getWinInfo() const;

 private:
  // Engine that is playing the requested level.
  Engine* engine_;
  // Input to the engine, based on player's keyboard inputs.
  EngineInput* inputs_;
  // Timer that ticks down the time until the player is allowed to start
  // playing (the 1... 2... 3... go! thing).
  Timer* startupTimer_;
  // Scene graph for the current level. This does all the heavy lifting to draw
  // the game state to the screen.
  Scene* scene_;

  DISALLOW_EVIL_CONSTRUCTORS(GameplayRenderer);
};

#endif

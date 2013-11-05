// Engine.h
// 
// Implements game mechanics. 
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Basics.h"
#include "DinoState.h"
#include <list>
using std::list;
#include <vector>
using std::vector;

class ChaserAgent;
class DinoState;
class EngineInput;
class Level;
class PropSpec;
class Timer;

enum EngineState {
  ES_RUNNING,
  ES_WON,
  ES_LOST
};

struct WinRecord {
  vector<long> oldTimes;
  long newTime;
  int par;
  int level;
  bool unlockedNextLevel;
};

class Engine {
 public:

  // Constructs object for first level, initializes player states. 
  Engine();

  // Constructs an engine to start playing the given level. 'level' must be
  // between 1 and Config::NUM_LEVELS, inclusive.
  explicit Engine(int level);

  // Frees resources used by the game engine.
  ~Engine();

  // Progresses the game state by a single timestep.
  EngineState evolve(const EngineInput& inputs);

  // What's the state of the engine?
  EngineState getEngineState() const;

  // Sets player vulnerability.
  void toggleInvincible();

  // Set invincibility to on (true) or off (false).
  void setInvincible(bool to);

  // Prevents the model from evolving.
  void toggleFrozen();

  // Is the game paused?
  bool isFrozen() const;

  // Get the level currently being played.
  const Level& getCurrentLevel() const;

  // Number of dots left in level.
  int getNumDotsLeft() const;

  // How long has the player been playing this level?
  long getMillisecondsSpentOnLevel() const;

  // What powerup is currently in effect?
  PowerupEffect getCurrentPowerup() const;

  // For how long?
  long getTimeLeftInPowerup() const;

  // Returns information about the player win. This is only safe to call once
  // evolve() has returned ES_WON; an assertion will fail otherwise. This
  // should only be called once. The caller is responsible for freeing the
  // returned record. This is kludgy, but it serves its purpose well enough.
  WinRecord* getWinInfo() const;

 private:
  // The model of the current level being played.
  Level* currentLevel_;    
  // Agents that control NPCs.
  ChaserAgent** agents_;   
  // Timer to time how long player has spent on current level.
  Timer* levelTimer_; 
  // Number of dots left in the current level.
  int numDotsLeft_;
  // The current powerup in effect.
  PowerupEffect currentEffect_;
  // How much longer the current powerup should last.
  Timer* powerupTimer_;
  // Game paused?
  bool isModelFrozen_;
  // Can the player be hurt?
  bool isPlayerInvincible_;
  // Is this the first evolution of the engine? (Hacky.)
  bool firstTick_;
  // The record of the player's performance in this level. Is NULL until
  // evolve() returns ES_WON.
  WinRecord* win_;
  // Is the game over yet?
  bool gameOver_;

  void init();
  void handleWin();

  DISALLOW_EVIL_CONSTRUCTORS(Engine);
};

#endif

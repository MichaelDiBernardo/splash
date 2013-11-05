// Level.h
// 
// Parses level specifications from file and maintains the state of
// all non-'intelligent' entities in the level (obstacles, goodies,
// etc.)
//
// This is meant to group together a lot of the entities that the Engine
// operates on, so many of the getters are not const because the Engine will
// mutate many of the internals of the Level.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <list>
#include <vector>
#include <string>
using std::list;
using std::vector;
using std::string;

#include "Basics.h"

class DinoState;
class PropSpec;

class Level {

 public:
  // Given the level number you want to instantiate, creates a new level
  // specification from the corresponding file. 'level' must be between 1 and
  // Config::NUM_LEVELS, inclusive.
  explicit Level(int level);

  // Frees resources used by this object.
  ~Level();

  // Gets the state of the player.
  DinoState* getPCState();

  // How many NPCs are in the level?
  int getNumNPCs() const;

  // What is the state of the ith NPC?
  DinoState* getNPCState(unsigned int i);

  // Returns a list of the props in this level.
  list<PropSpec*>* getProps();

  // Get the dots in this level.
  list<PropSpec*>* getDots();

  // Get the powerups in this level.
  list<PropSpec*>* getPowerups();

  // Const getters for when you want to snoop without changing things.
  const DinoState& getPCStateConst() const;
  const vector<DinoState*>& getNPCStatesConst() const;
  const list<PropSpec*>& getPropsConst() const;
  const list<PropSpec*>& getDotsConst() const;
  const list<PropSpec*>& getPowerupsConst() const;

  // Get the record times for this level.
  const vector<long>& getRecordTimes() const;

  // Get height of level.
  double getHeight() const;

  // Get width of level.
  double getWidth() const;

  // Get the par for the level, in seconds.
  int getPar() const;

  // Get this level's number.
  int getLevelNumber() const;

  // Change the records and update the number of unlocked levels, if necessary,
  // given the amount of time that the player took to complete the level.
  void handleWin(long newTime) const;

  // Count how many levels have been unlocked by the player thus far. (Involves
  // file ops.)
  static int getNumLevelsUnlocked();

  // Increment the number of levels that have been unlocked by the player.
  // (Involves file ops.)
  static void unlockNextLevel();

 private:
  // The player's state.
  DinoState* pcState_;
  // The enemy dino states.
  vector<DinoState*> npcStates_;
  // The various obstacle props scattered around the level.
  list<PropSpec*> propSpecs_;
  // The dots in the level.
  list<PropSpec*> dots_;
  // The powerups in the level.
  list<PropSpec*> powerups_;
  // Record times for this level.
  vector<long> recordTimes_;

  // Max unit in z-axis of level.
  double height_;
  // Max unit in x-axis of level.
  double width_;
  // How quickly must this level be finished in order to clear it? Measured in
  // seconds, I believe.
  int par_;
  // What is the number of the level represented here?
  int levelNumber_;

  DISALLOW_EVIL_CONSTRUCTORS(Level);

  double getAngleForChar(char a) const;
};

#endif

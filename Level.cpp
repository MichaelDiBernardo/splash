#include "Level.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "os.h"
#include "Config.h"
#include "Format.h"
#include "PropSpec.h"
#include "Orientation.h"
#include "DinoState.h"
using namespace std;

double getAngleForChar(char a) {
  if (a == 'E')
    return 0;
  else if (a == 'N')
    return M_PI/2;
  else if (a == 'W')
    return M_PI;
  else if (a == 'S')
    return 3*M_PI/2;
  else {
    assert(false);
    return 0;
  }
}

Orientation makeOrientation(double width, stringstream* ss) {
  double x, y;
  char a;
  *ss >> x; x = width - x; *ss >> y; *ss >> a;
  return Orientation(x, y, getAngleForChar(a));
}

PropSpec* makeProp(const string& type, double width, int id, stringstream* ss) {
  double x, y, xDim, yDim;
  *ss >> x; x = width - x; *ss >> y; *ss >> xDim; *ss >> yDim;
  if (type == "ISLAND") 
    return new PropSpec(id, ISLAND_PROP, x, y, xDim, yDim);
  else if (type == "BOX") 
    return new PropSpec(id, BOX_PROP, x, y, xDim, yDim);
  else if (type == "TORCH")
    return new PropSpec(id, TORCH_PROP, x, y, xDim, yDim);
  else if (type == "THRONE")
    return new PropSpec(id, THRONE_PROP, x, y, xDim, yDim);
  else if (type == "TROPHY") 
    return new PropSpec(id, TROPHY_PROP, x, y, xDim, yDim);
  else if (type == "DOT") 
    return new PropSpec(id, DOT_PROP, x, y, Config::DOT_DIM, Config::DOT_DIM);
  else if (type == "FEAR_POWERUP") 
    return new PropSpec(id, FEAR_POWERUP_PROP, x, y, Config::POWERUP_DIM, Config::POWERUP_DIM);
  else if (type == "FREEZE_POWERUP") 
    return new PropSpec(id, FREEZE_POWERUP_PROP, x, y, Config::POWERUP_DIM, Config::POWERUP_DIM);
  else if (type == "SPEED_POWERUP") 
    return new PropSpec(id, SPEED_POWERUP_PROP, x, y, Config::POWERUP_DIM, Config::POWERUP_DIM);
  else return NULL;
}

Level::Level(int level) : levelNumber_(level) {
  int lnum = 0;
  int id = 0;
  string filename = "l" + Format::intToString(level) + ".txt";
  ifstream in(filename.c_str());

  if (!in.is_open()) {
    cerr << "File " << filename << " could not be opened for reading." << endl;
    exit(-1);
  }

  while (!in.eof()) {
    lnum++;
    
    char rawLine[1024];
    in.getline(rawLine, 1024);

    string line(rawLine);

    stringstream ss(line);

    string type;
    ss >> type;

    if (type == "") break;

    if (type == "LEVEL_HEIGHT") {
      ss >> height_;
    } else if (type == "LEVEL_WIDTH") {
      ss >> width_;
    } else if (type == "LEVEL_PAR") {
      ss >> par_;
    } else if (type == "PLAYER_STARTING_ORIENTATION") {
      pcState_ = new DinoState(makeOrientation(width_, &ss), CHAR_PC); 
    } else if (type == "NPC_STARTING_ORIENTATION") {
      npcStates_.push_back(new DinoState(makeOrientation(width_, &ss), CHAR_NPC)); 
    } else if (type == "DOT_LINE") {
      double startx, starty, endx, endy;
      ss >> startx; ss >> starty; ss >> endx; ss >> endy;
      for (double x = startx; x <= endx; ++x) {
        for (double y = starty; y <= endy; ++y) {
          PropSpec* curP = new PropSpec(id, DOT_PROP, width_ - x, y, Config::DOT_DIM, Config::DOT_DIM);
          dots_.push_back(curP);
          ++id;
        }
      }
    } else {
      // See if it's a prop.
      PropSpec* prop = makeProp(type, width_, id, &ss);
      if (prop != NULL) {
        if (type == "DOT") 
          dots_.push_back(prop);
        else if (type == "FEAR_POWERUP" || type == "SPEED_POWERUP" || type == "FREEZE_POWERUP")
          powerups_.push_back(prop);
        else
          propSpecs_.push_back(prop);
        ++id;
      } else {
        cerr << "Encountered unknown entity " << type << " while parsing level file " << filename <<  " at line " << lnum << endl;
        assert(false);
      }
    }
  }
  in.close();

  string timesfn = "l" + Format::intToString(level) + ".t";
  ifstream tin(timesfn.c_str());

  if (!tin.is_open()) {
    cerr << "File " << timesfn << " could not be opened for reading." << endl;
    exit(-1);
  }

  for (int i = 0; i < Config::NUM_RECORD_TIMES; ++i) {
    int record;
    tin >> record;
    recordTimes_.push_back(record);
  }
  tin.close();
}

Level::~Level() {
  delete pcState_;
  
  STLDeleteContainerPointers(npcStates_.begin(), npcStates_.end());
  STLDeleteContainerPointers(propSpecs_.begin(), propSpecs_.end());
}

DinoState* Level::getPCState() {
  return pcState_;
}

int Level::getNumNPCs() const {
  return npcStates_.size();
}

DinoState* Level::getNPCState(unsigned int i) {
  assert(i >= 0);
  assert(i < npcStates_.size());
  return npcStates_[i];
}

list<PropSpec*>* Level::getProps() {
  if (propSpecs_.size() == 0)
    return NULL;
  else
    return &propSpecs_;
}

list<PropSpec*>* Level::getDots() {
  return &dots_;
}

list<PropSpec*>* Level::getPowerups() {
  return &powerups_;
}

double Level::getHeight() const {
  return height_;
}

double Level::getWidth() const {
  return width_;
}

int Level::getPar() const {
  return par_;
}

const DinoState& Level::getPCStateConst() const {
  return *pcState_;
}

const vector<DinoState*>& Level::getNPCStatesConst() const {
  return npcStates_;
}

const list<PropSpec*>& Level::getPropsConst() const {
  return propSpecs_;
}

const list<PropSpec*>& Level::getDotsConst() const {
  return dots_;
}

const list<PropSpec*>& Level::getPowerupsConst() const {
  return powerups_;
}

const vector<long>& Level::getRecordTimes() const {
  return recordTimes_;
}

int Level::getLevelNumber() const {
  return levelNumber_;
}

void Level::handleWin(long newTime) const {
  if (levelNumber_ == getNumLevelsUnlocked() && 
      levelNumber_ != Config::NUM_LEVELS && 
      newTime <= getPar() * 1000) {
    unlockNextLevel();
  }

  string filename = "l" + Format::intToString(levelNumber_) + ".t";
  ofstream out(filename.c_str());
  if (!out.is_open()) {
    cerr << "File " << filename << " could not be opened for writing." << endl;
    exit(-1);
  }

  // TODO: CODE DUPLICATION but it's only twice, so we leave it for now :)
  // (Also in WinscreenRenderer.)
  int newTimeIndex;
  for (newTimeIndex = 0; newTimeIndex < Config::NUM_RECORD_TIMES; ++newTimeIndex) {
    if (newTime < recordTimes_[newTimeIndex]) break;
  }

  int ind = 0;
  for (int i = 0; i < Config::NUM_RECORD_TIMES; ++i) {
    if (i == newTimeIndex) {
      out << newTime << endl;
    } else {
      out << recordTimes_[ind] << endl;
      ++ind;
    }
  }
  out.close();
}

static const char* kLevelLocksFilename = "levels.dat";

int Level::getNumLevelsUnlocked() {
  ifstream in(kLevelLocksFilename);

  if (!in.is_open()) {
    cerr << "File " << kLevelLocksFilename << " could not be opened for reading." << endl;
    exit(-1);
  }

  int levelsUnlocked;
  in >> levelsUnlocked;
  in.close();
  assert(levelsUnlocked > 0 && levelsUnlocked <= Config::NUM_LEVELS);
  return levelsUnlocked;
}

void Level::unlockNextLevel() {
  int levelsUnlocked = getNumLevelsUnlocked();
  ++levelsUnlocked;
  
  ofstream out(kLevelLocksFilename);
  if (!out.is_open()) {
    cerr << "File " << kLevelLocksFilename << " could not be opened for writing." << endl;
    exit(-1);
  }
  out << levelsUnlocked;
  out.close();
}

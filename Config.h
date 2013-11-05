// Stores game configuration. Hacky, but it works. Everything is immutable
// except for quantities that must be changed to accommodate changes in the
// frame rate.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None
#ifndef __CONFIG_H__
#define __CONFIG_H__
class ColorSpec;

#include "os.h"
#include <string>
using std::string;

class Config {
 public:
  static double changeFrameRate(double increment);

  static double FRAME_RATE;

  static double PLAYER_FORWARD_ACCELERATION;
  static double PLAYER_MAX_FORWARD_VELOCITY;

  static const double PLAYER_DRAG;

  static double PLAYER_BACKWARD_ACCELERATION;
  static double PLAYER_MAX_BACKWARD_VELOCITY;

  static double PLAYER_TURN_VELOCITY;

  static double BOT_FORWARD_ACCELERATION;
  static double BOT_MAX_FORWARD_VELOCITY;

  static const double BOT_DRAG;

  static double BOT_BACKWARD_ACCELERATION;
  static double BOT_MAX_BACKWARD_VELOCITY;

  static double BOT_TURN_VELOCITY;

  static const double BOX_OFFSET;

  static const double DINO_RADIUS;

  static const double DOT_DIM;
  static const double DOT_CENTER_HEIGHT;

  static const double POWERUP_DIM;
  static const double POWERUP_CENTER_HEIGHT;

  static const long POWERUP_DURATION_IN_MICROSECONDS;

  // View stuff
  static const double BOX_HEIGHT;

  static const double DEFAULT_CAMERA_FOLLOW_DISTANCE;
  static const double MIN_CAMERA_DISTANCE;
  static const double MAX_CAMERA_DISTANCE;
  static const double CAMERA_ZOOM_INCREMENT;

  static const double DEFAULT_CAMERA_HEIGHT;
  static const double MIN_CAMERA_HEIGHT;
  static const double MAX_CAMERA_HEIGHT;
  static const double CAMERA_HEIGHT_INCREMENT;

  static const double ISLAND_HEIGHT_ABOVE_WATER;
  static const double OCEAN_FLOOR_DEPTH;

  static const int DEFAULT_SCREEN_WIDTH;
  static const int DEFAULT_SCREEN_HEIGHT;

  // Colours for scene.
  static const ColorSpec* BOX_COLOR; 
  static const ColorSpec* OCEAN_FLOOR_COLOR;
  static const ColorSpec* OCEAN_WATER_COLOR;
  static const ColorSpec* SKY_COLOR;
  static const ColorSpec* DOT_COLOR;
  static const ColorSpec* FEAR_POWERUP_COLOR;
  static const ColorSpec* FREEZE_POWERUP_COLOR;
  static const ColorSpec* SPEED_POWERUP_COLOR;

  // Colours for player dino.
  static const ColorSpec* PLAYER_BODY_COLOR;
  static const ColorSpec* PLAYER_HEAD_COLOR;
  static const ColorSpec* PLAYER_SPIKE_COLOR;
  static const ColorSpec* PLAYER_NECK_COLOR;
  static const ColorSpec* PLAYER_TAIL_COLOR;
  static const ColorSpec* PLAYER_LEG_COLOR;
  static const ColorSpec* PLAYER_EYE_COLOR;
  static const ColorSpec* PLAYER_PUPIL_COLOR;
  static const ColorSpec* PLAYER_TONGUE_COLOR;

  static const ColorSpec* BOT_BODY_COLOR;
  static const ColorSpec* BOT_HEAD_COLOR;
  static const ColorSpec* BOT_SPIKE_COLOR;
  static const ColorSpec* BOT_NECK_COLOR;
  static const ColorSpec* BOT_TAIL_COLOR;
  static const ColorSpec* BOT_LEG_COLOR;
  static const ColorSpec* BOT_EYE_COLOR;
  static const ColorSpec* BOT_PUPIL_COLOR;
  static const ColorSpec* BOT_TONGUE_COLOR;

  static const ColorSpec* THRONE_COLOR;
  static const ColorSpec* TORCH_COLOR;
  static const ColorSpec* TROPHY_COLOR;

  // Sunlight 'stats'
  static const GLfloat SUNLIGHT_AMB[4];
  static const GLfloat SUNLIGHT_DIF[4];
  static const GLfloat SUNLIGHT_SPEC[4];

  static const GLfloat FEAR_POWERUP_AMB[4];
  static const GLfloat FEAR_POWERUP_DIF[4];
  static const GLfloat FEAR_POWERUP_SPEC[4];

  static const GLfloat FREEZE_POWERUP_AMB[4];
  static const GLfloat FREEZE_POWERUP_DIF[4];
  static const GLfloat FREEZE_POWERUP_SPEC[4];

  static const GLfloat SPEED_POWERUP_AMB[4];
  static const GLfloat SPEED_POWERUP_DIF[4];
  static const GLfloat SPEED_POWERUP_SPEC[4];

  static const GLfloat SHINY_MAT_AMB[4];
  static const GLfloat SHINY_MAT_DIF[4];
  static const GLfloat SHINY_MAT_SPEC[4];

  // Animation files.
  static const char* DINO_FORWARD_ANIMATION_FILE_PATH;
  static const char* DINO_BACKWARD_ANIMATION_FILE_PATH;
  static const char* DINO_TURN_LEFT_ANIMATION_FILE_PATH;
  static const char* DINO_TURN_RIGHT_ANIMATION_FILE_PATH;

  // Obj files.
  static const char* TORCH_OBJ_FILE;
  static const char* THRONE_OBJ_FILE;
  static const char* TROPHY_OBJ_FILE;

  static const char* OCEAN_FLOOR_TEXTURE;
  static const char* WALL_TEXTURE;
  static const char* WATER_TEXTURE;
  static const char* SKY_TEXTURE;
  static const char* SPLASHSCREEN_IMAGE;
  static const char* MENU_IMAGE;
  static const char* ENDGAME_IMAGE;

  static const int NUM_LEVELS;
  static const int NUM_RECORD_TIMES;

  static const long COUNTDOWN_LENGTH; 

  static const long ENDGAME_WAIT; 

  static const double MAX_2D_COORD;

 private:
  static const string LEVEL_ONE_FILE_PATH;
};
#endif

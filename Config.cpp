#include "Config.h"
#include <math.h>
#include <assert.h>
#include "ColorSpec.h"

const string Config::LEVEL_ONE_FILE_PATH = "l1.txt";

double Config::FRAME_RATE = 40;

const double Config::PLAYER_DRAG = 0.2;

double Config::PLAYER_FORWARD_ACCELERATION = 0.2/FRAME_RATE;
double Config::PLAYER_MAX_FORWARD_VELOCITY = 10/FRAME_RATE;

double Config::PLAYER_BACKWARD_ACCELERATION = -0.2/FRAME_RATE;
double Config::PLAYER_MAX_BACKWARD_VELOCITY = -10/FRAME_RATE;

double Config::PLAYER_TURN_VELOCITY = (M_PI)/FRAME_RATE;

double Config::BOT_FORWARD_ACCELERATION = 0.2/FRAME_RATE;
double Config::BOT_MAX_FORWARD_VELOCITY = 5/FRAME_RATE;

double Config::BOT_BACKWARD_ACCELERATION = -0.2/FRAME_RATE;
double Config::BOT_MAX_BACKWARD_VELOCITY = -5/FRAME_RATE;

double Config::BOT_TURN_VELOCITY = (M_PI/1.5)/FRAME_RATE;

const double Config::BOX_OFFSET = 0.28;

const double Config::DINO_RADIUS = 0.4;

const double Config::DOT_DIM = 0.06;
const double Config::DOT_CENTER_HEIGHT = 0.3;

const double Config::POWERUP_DIM = 0.2;
const double Config::POWERUP_CENTER_HEIGHT = 0.3;

const long Config::POWERUP_DURATION_IN_MICROSECONDS = 8 * 1000 * 1000;

// View stuff.
const double Config::BOX_HEIGHT = 2.0;
const double Config::DEFAULT_CAMERA_HEIGHT = 2;
const double Config::DEFAULT_CAMERA_FOLLOW_DISTANCE = 3;
const double Config::MIN_CAMERA_DISTANCE = 1;
const double Config::MAX_CAMERA_DISTANCE = 6;
const double Config::CAMERA_ZOOM_INCREMENT = 0.5;
const double Config::ISLAND_HEIGHT_ABOVE_WATER = 0.5;
const double Config::OCEAN_FLOOR_DEPTH = -1.0;

const double Config::MIN_CAMERA_HEIGHT = 0.5;
const double Config::MAX_CAMERA_HEIGHT = 10;
const double Config::CAMERA_HEIGHT_INCREMENT = 0.5;

const int Config::DEFAULT_SCREEN_WIDTH = 800;
const int Config::DEFAULT_SCREEN_HEIGHT = 600;

const ColorSpec* Config::BOX_COLOR = new ColorSpec(0.9, 0.9, 0.9);
const ColorSpec* Config::OCEAN_FLOOR_COLOR = new ColorSpec(1, 1, 0);
const ColorSpec* Config::OCEAN_WATER_COLOR = new ColorSpec(0, 0.25, 1.0, 0.75);
const ColorSpec* Config::SKY_COLOR = new ColorSpec(0.3, 0.45, 0.75);
const ColorSpec* Config::DOT_COLOR = new ColorSpec(0.0, 0.0, 0.0);

const ColorSpec* Config::FEAR_POWERUP_COLOR = new ColorSpec(1.0, 0.0, 0.0, 0.7);
const ColorSpec* Config::FREEZE_POWERUP_COLOR = new ColorSpec(0.0, 0.0, 1.0, 0.7);
const ColorSpec* Config::SPEED_POWERUP_COLOR = new ColorSpec(0.0, 1.0, 0.0, 0.7);

const ColorSpec* Config::PLAYER_BODY_COLOR = new ColorSpec(0.373, 0.627, 0.875);
const ColorSpec* Config::PLAYER_HEAD_COLOR = new ColorSpec(0.373, 0.627, 0.875);
const ColorSpec* Config::PLAYER_SPIKE_COLOR = new ColorSpec(0.565, 0.063, 0.314);
const ColorSpec* Config::PLAYER_NECK_COLOR = new ColorSpec(0.373, 0.627, 0.875);
const ColorSpec* Config::PLAYER_TAIL_COLOR = new ColorSpec(0.373, 0.627, 0.875);
const ColorSpec* Config::PLAYER_LEG_COLOR = new ColorSpec(0.373, 0.627, 0.875);
const ColorSpec* Config::PLAYER_EYE_COLOR = new ColorSpec(1, 1, 1);
const ColorSpec* Config::PLAYER_PUPIL_COLOR = new ColorSpec(0.1, 0.1, 0.1);
const ColorSpec* Config::PLAYER_TONGUE_COLOR = new ColorSpec(0.9, 0.56, 0.59);

const ColorSpec* Config::BOT_BODY_COLOR = new ColorSpec(0.5, 0, 0);
const ColorSpec* Config::BOT_HEAD_COLOR = BOT_BODY_COLOR;
const ColorSpec* Config::BOT_SPIKE_COLOR = new ColorSpec(0, 0, 0);
const ColorSpec* Config::BOT_NECK_COLOR = BOT_BODY_COLOR;
const ColorSpec* Config::BOT_TAIL_COLOR = BOT_BODY_COLOR;
const ColorSpec* Config::BOT_LEG_COLOR = BOT_BODY_COLOR;
const ColorSpec* Config::BOT_EYE_COLOR = new ColorSpec(1, 1, 0);
const ColorSpec* Config::BOT_PUPIL_COLOR = new ColorSpec(0.1, 0.1, 0.1);
const ColorSpec* Config::BOT_TONGUE_COLOR = new ColorSpec(0, 0, 0);

const ColorSpec* Config::TORCH_COLOR = new ColorSpec(0.72, 0.45, 0.20);
const ColorSpec* Config::THRONE_COLOR = new ColorSpec(0.8, 0.8, 0.8);
const ColorSpec* Config::TROPHY_COLOR = new ColorSpec(0.6, 0.4, 0.0);

const GLfloat Config::SUNLIGHT_AMB[] = { 0.15, 0.15, 0.15, 0.0 };
const GLfloat Config::SUNLIGHT_DIF[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat Config::SUNLIGHT_SPEC[] = { 1.0, 1.0, 1.0, 1.0 };

const GLfloat Config::FEAR_POWERUP_AMB[] = { 0.0, 0.0, 0.0, 0.0 };
const GLfloat Config::FEAR_POWERUP_DIF[] = { 1.0, 0.0, 0.0, 1.0 };
const GLfloat Config::FEAR_POWERUP_SPEC[] = { 1.0, 0.0, 0.0, 1.0 };

const GLfloat Config::FREEZE_POWERUP_AMB[] = { 0.0, 0.0, 0.0, 0.0 };
const GLfloat Config::FREEZE_POWERUP_DIF[] = { 0.0, 0.0, 1.0, 1.0 };
const GLfloat Config::FREEZE_POWERUP_SPEC[] = { 0.0, 0.0, 1.0, 1.0 };

const GLfloat Config::SPEED_POWERUP_AMB[] = { 0.0, 0.0, 0.0, 0.0 };
const GLfloat Config::SPEED_POWERUP_DIF[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat Config::SPEED_POWERUP_SPEC[] = { 0.0, 1.0, 0.0, 1.0 };
    
const GLfloat Config::SHINY_MAT_AMB[] = {0.117647, 0.117647, 0.117647};
const GLfloat Config::SHINY_MAT_DIF[] = {0.752941, 0.752941, 0.752941};
const GLfloat Config::SHINY_MAT_SPEC[] = {0.752941, 0.752941, 0.752941};

const char* Config::DINO_FORWARD_ANIMATION_FILE_PATH = "mf.txt";
const char* Config::DINO_BACKWARD_ANIMATION_FILE_PATH = "mb.txt";
const char* Config::DINO_TURN_LEFT_ANIMATION_FILE_PATH = "tl.txt";
const char* Config::DINO_TURN_RIGHT_ANIMATION_FILE_PATH = "tr.txt";

const char* Config::TORCH_OBJ_FILE = "torch.obj.txt";
const char* Config::THRONE_OBJ_FILE = "throne.obj.txt";
const char* Config::TROPHY_OBJ_FILE = "trophy.obj.txt";

const char* Config::OCEAN_FLOOR_TEXTURE = "of.sgi.txt";
const char* Config::WALL_TEXTURE = "wall.sgi.txt";
const char* Config::WATER_TEXTURE = "water.sgi.txt";
const char* Config::SKY_TEXTURE = "sky.sgi.txt";
const char* Config::SPLASHSCREEN_IMAGE = "title.sgi.txt";
const char* Config::MENU_IMAGE = "levelselect.sgi.txt";
const char* Config::ENDGAME_IMAGE = "end.sgi.txt";

const int Config::NUM_LEVELS = 4;
const int Config::NUM_RECORD_TIMES = 5;
const long Config::COUNTDOWN_LENGTH = 6 * 1000;

const long Config::ENDGAME_WAIT = 5 * 1000;

const double Config::MAX_2D_COORD = 3000.0;

double Config::changeFrameRate(double increment) {
  FRAME_RATE += increment;
  if (FRAME_RATE < 20)
    FRAME_RATE = 20;
  else if (FRAME_RATE > 60)
    FRAME_RATE = 60;

  PLAYER_FORWARD_ACCELERATION = 0.2 / FRAME_RATE;
  PLAYER_MAX_FORWARD_VELOCITY = 10 / FRAME_RATE;

  PLAYER_BACKWARD_ACCELERATION = -0.2 / FRAME_RATE;
  PLAYER_MAX_BACKWARD_VELOCITY = -10 / FRAME_RATE;

  PLAYER_TURN_VELOCITY = (M_PI) / FRAME_RATE;

  BOT_FORWARD_ACCELERATION = 0.2 / FRAME_RATE;
  BOT_MAX_FORWARD_VELOCITY = 5.0 / FRAME_RATE;

  BOT_BACKWARD_ACCELERATION = -0.2 / FRAME_RATE;
  BOT_MAX_BACKWARD_VELOCITY = -5.0 / FRAME_RATE;

  BOT_TURN_VELOCITY = (M_PI / 1.5) / FRAME_RATE;

  return FRAME_RATE;
}

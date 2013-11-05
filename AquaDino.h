// Some dino-related constants that I didn't want cluttering up the main file.
// This is stolen from A1. So ugly.
// 
// Michael DiBernardo
#ifndef __AQUA_DINO_H__
#define __AQUA_DINO_H__

// Number of joints and animation parameters required to describe the lil guy.
#define AQUA_DINO_NUM_JOINTS 18
#define AQUA_DINO_NUM_PARAMS 54

// Indices into joint node array.
#define J_NECK_1 0
#define J_NECK_2 1
#define J_NECK_3 2
#define J_HEAD 3
#define J_TAIL_1 4
#define J_TAIL_2 5
#define J_TAIL_3 6
#define J_LEG_BL_1 7
#define J_LEG_BL_2 8
#define J_LEG_BR_1 9
#define J_LEG_BR_2 10
#define J_LEG_FL_1 11
#define J_LEG_FL_2 12
#define J_LEG_FR_1 13
#define J_LEG_FR_2 14
#define J_BODY 15
#define J_LEFT_EYE 16
#define J_RIGHT_EYE 17

// Indices into keyframe arrays.
#define P_DINO_X 0
#define P_DINO_Y 1
#define P_DINO_Z 2

#define P_HEAD_UP_DOWN 3
#define P_HEAD_LEFT_RIGHT 4

#define P_NECK_1_SEG_UP_DOWN 5
#define P_NECK_1_SEG_LEFT_RIGHT 6
#define P_NECK_1_SEG_MED_LAT 7

#define P_NECK_2_SEG_UP_DOWN 8
#define P_NECK_2_SEG_LEFT_RIGHT 9
#define P_NECK_2_SEG_MED_LAT 10

#define P_NECK_3_SEG_UP_DOWN 11
#define P_NECK_3_SEG_LEFT_RIGHT 12
#define P_NECK_3_SEG_MED_LAT 13

#define P_TAIL_1_SEG_UP_DOWN 14
#define P_TAIL_1_SEG_LEFT_RIGHT 15
#define P_TAIL_1_SEG_TWIST 16

#define P_TAIL_2_SEG_UP_DOWN 17
#define P_TAIL_2_SEG_LEFT_RIGHT 18
#define P_TAIL_2_SEG_TWIST 19

#define P_TAIL_3_SEG_UP_DOWN 20
#define P_TAIL_3_SEG_LEFT_RIGHT 21
#define P_TAIL_3_SEG_TWIST 22

#define P_FL_HIP_UP_DOWN 23
#define P_FL_HIP_LEFT_RIGHT 24
#define P_FL_HIP_TWIST 25

#define P_FL_KNEE_UP_DOWN 26
#define P_FL_KNEE_LEFT_RIGHT 27
#define P_FL_KNEE_TWIST 28

#define P_FR_HIP_UP_DOWN 29
#define P_FR_HIP_LEFT_RIGHT 30
#define P_FR_HIP_TWIST 31

#define P_FR_KNEE_UP_DOWN 32
#define P_FR_KNEE_LEFT_RIGHT 33
#define P_FR_KNEE_TWIST 34

#define P_BL_HIP_UP_DOWN 35
#define P_BL_HIP_LEFT_RIGHT 36
#define P_BL_HIP_TWIST 37

#define P_BL_KNEE_UP_DOWN 38
#define P_BL_KNEE_LEFT_RIGHT 39
#define P_BL_KNEE_TWIST 40

#define P_BR_HIP_UP_DOWN 41
#define P_BR_HIP_LEFT_RIGHT 42
#define P_BR_HIP_TWIST 43

#define P_BR_KNEE_UP_DOWN 44
#define P_BR_KNEE_LEFT_RIGHT 45
#define P_BR_KNEE_TWIST 46

#define P_BODY_PITCH 47
#define P_BODY_YAW 48
#define P_BODY_ROLL 49

#define P_LEFT_EYE_UP_DOWN 50
#define P_LEFT_EYE_LEFT_RIGHT 51

#define P_RIGHT_EYE_UP_DOWN 52
#define P_RIGHT_EYE_LEFT_RIGHT 53
#endif

#pragma once
//level = 0~6
typedef enum DIRECTION {
	LEFT_6,
	LEFT_5,
	LEFT_4,
	LEFT_3,
	LEFT_2,
	LEFT_1,
	MID,
	RIGHT_1,
	RIGHT_2,
	RIGHT_3,
	RIGHT_4,
	RIGHT_5,
	RIGHT_6
}FishDirections;

//speed level 0~15(0~e)
typedef enum SPEED{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5,
	LEVEL_6,
	LEVEL_7,
	LEVEL_8,
	LEVEL_9,
	LEVEL_10,
	LEVEL_11,
	LEVEL_12,
	LEVEL_13,
	LEVEL_14,
	LEVEL_15
}FishSpeed;

//Constant definitions
#define ENABLE_JOINT_1 0x8
#define ENABLE_JOINT_2 0x4
#define ENABLE_JOINT_3 0x2
#define ENABLE_JOINT_4 0x1
#define ENABLE_JOINT_MAX 0xf
#define ENABLE_JOINT_MIN 0x0

//Depth
#define MAX_DEPTH 150
#define MIN_DEPTH 11
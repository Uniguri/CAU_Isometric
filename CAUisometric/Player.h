#pragma once
#include <bangtal.h>
#include <stdio.h>
#include "constant_value.h"
#include "bullet.h"
#include "turret.h"

#define NUMBER_OF_PLAYER_IDLE_IMAGE_FOR_EACH_DIR 16
#define NUMBER_OF_PLAYER_MOVE_IMAGE_FOR_EACH_DIR 17
#define NUMBER_OF_PLAYER_ATTACK_IMAGE_FOR_EACH_DIR 18

enum PlayerState
{
	IDLE, WALK, ATTACK, PLAYER_STATTE_SIZE
};

enum DirectionOfPlayerFace
{
	DOWN, DOWN_RIGHT, RIGHT, RIGHT_UP, UP, UP_LEFT, LEFT, LEFT_DOWN, DIRECTION_OF_PLAYER_FACE_SIZE
};

struct Player
{
	ObjectID obj;
	SceneID scene;
	DirectionOfPlayerFace direction;
	PlayerState state;
	int image_frame;
	int image_frame_counter;
	int speed, dx, dy;
	int x, y;
	char health;
	bool is_dead;
};

struct heart_struct
{
	SceneID scene;
	ObjectID heart[5];
	int heart_y = 500, heart_x[5] = { 565, 595, 625, 655, 685 };
	int num_heart = 5;
};
void heart_function();
void ShowHeart();

void PlayerTimerCallback(TimerID timer);
void PlayerKeyboardCallback(KeyCode code, KeyState state);

void RefreshPlayer();

void InitPlayer();

bool IsOutOfMap();

void ResetPlayer();

void MoveLevelAnimation();

void PlayerAttack();
void PlayerHitted();
bool IsDead();
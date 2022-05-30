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

void PlayerTimerCallback(TimerID timer, Player* player, ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int* level, SceneID scene[MAX_LEVEL], Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET]);
void PlayerKeyboardCallback(KeyCode code, KeyState state, Player* player);

void RefreshPlayer(Player* player);

void InitPlayer(Player* player, const SceneID scene);

bool IsOutOfMap(Player* player, const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], const int level);

void ResetPlayer(Player* player, const SceneID scene);

void MoveLevelAnimation(Player* player);

void PlayerAttack(Player* player);
void PlayerHitted(Player* player, const Bullet* bullet);
bool IsDead(Player* player);
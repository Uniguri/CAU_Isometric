#pragma once
#include <bangtal.h>
#include <stdio.h>
#include "constant_value.h"
#include "bullet.h"

struct Player
{
	ObjectID obj;
	SceneID scene;
	int speed, dx, dy;
	int x, y;
	char health;
	bool is_attacking;
	bool is_dead;
};

void PlayerTimerCallback(TimerID timer, Player* player, ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1]);
void PlayerKeyboardCallback(KeyCode code, KeyState state, Player* player);

void InitPlayer(Player* player, const SceneID scene);

bool IsOutOfMap(Player* player, const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], const int level);

void PlayerAttack(Player* player);
void PlayerHitted(Player* player, const Bullet* bullet);
bool IsDead(Player* player);
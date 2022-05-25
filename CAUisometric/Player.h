#pragma once
#include "constant_value.h"
#include <bangtal.h>

struct Player
{
	ObjectID obj;
	SceneID scene;
	int speed, dx, dy;
	int x, y;
	char health;
	bool isAttacking;
};

void PlayerTimerCallback(TimerID timer, Player* player, ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH]);
void PlayerKeyboardCallback(KeyCode code, KeyState state, Player* player);

void InitPlayer(Player* player, const SceneID scene);

void PlayerAttack(Player* player);
void PlayerHitted(Player* player, const char damage);
bool IsDead(Player* player);
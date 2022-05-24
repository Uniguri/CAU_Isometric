#pragma once
#include "constant_value.h"
#include <bangtal.h>

struct Player
{
	ObjectID obj;
	SceneID scene;
	int speed, dx, dy;
	int x, y;
};

void PlayerTimerCallback(TimerID timer, Player* player);
void PlayerKeyboardCallback(KeyCode code, KeyState state, Player* player);

void PlayerInit(Player* player, SceneID scene);
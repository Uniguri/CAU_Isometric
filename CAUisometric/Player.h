#pragma once
#include <bangtal.h>

struct Player
{
	ObjectID obj;
	SceneID scene;
	int speed, dx, dy;
	int x, y;
};

void Player_timerCallback(TimerID timer, Player* player);
void Player_keyboardCallback(KeyCode code, KeyState state, Player* player);

void Player_init(Player* player, SceneID scene);
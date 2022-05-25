#pragma once

#include "constant_value.h"
#include <bangtal.h>

struct Bullet
{
	ObjectID obj;
	SceneID scene;
	int x, y;
	int speed;
	bool is_deleted;
};

void InitBullet(Bullet* bullet, SceneID scene, const int x, const int y, const int speed);
void MoveBullet(Bullet* bullet);
void RefreshBullet(Bullet* bullet);
void DeleteBullet(Bullet* bullet);
bool IsDeleted(Bullet* bullet)
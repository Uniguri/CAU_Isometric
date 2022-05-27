#pragma once

#include "constant_value.h"
#include <bangtal.h>

struct Bullet
{
	ObjectID obj;
	SceneID scene;
	int x, y;
	int dx, dy;
	int speed;
	bool is_deleted;
};

void InitBullet(Bullet* bullet, SceneID scene, const int x, const int y, const int speed);
void MoveBullet(Bullet* bullet, const int additional_dx, const int additiona_dy);
void RefreshBullet(Bullet* bullet);
void DeleteBullet(Bullet* bullet);
bool IsDeleted(Bullet* bullet)

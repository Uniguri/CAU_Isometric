#pragma once

#include <bangtal.h>
#include <math.h>
#include "constant_value.h"
#include "types.h"
#include "utility.h"

struct Bullet
{
	ObjectID obj;
	SceneID scene;
	Vec2d direction_vec;
	double x, y;
	int speed;
	bool is_deleted;
};

void BulletTimerCallback(TimerID timer, Bullet bullets[MAX_NUMBER_OF_BULLET], const int dx, const int dy);

void InitBullet(Bullet* bullet, SceneID scene);
void InitBulletSystem(void);
void DeleteBullet(Bullet* bullet);
void SetBullet(Bullet* bullet, SceneID scene, const int x, const int y, const int speed, const Vec2d direction_vec);
void MoveBullet(Bullet* bullet, const int additional_dx, const int additional_dy);
void RefreshBullet(Bullet* bullet, const int additional_dx, const int additional_dy);

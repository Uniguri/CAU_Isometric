#pragma once

#include <bangtal.h>
#include <math.h>
#include "constant_value.h"
#include "types.h"
#include "utility.h"

enum BulletType :unsigned char
{
	MINT_BULLET = 0, ICE_BULLET, GRAY_BULLET, PURPLE_BULLET, RED_BULLET, WHITE_BULLET, BULLET_TYPE_SIZE
};

struct Bullet
{
	ObjectID obj;
	SceneID scene;
	Vec2d direction_vec;
	double x, y;
	int speed;
	bool is_deleted;
};

void BulletTimerCallback(TimerID timer, const int dx, const int dy);

void InitBullet(int i);
void InitBulletSystem(void);
void DeleteBullet(int i);
void SetBullet(const int x, const int y, const int speed, const Vec2d direction_vec, int i);
void ChangeBulletType(BulletType type);
void MoveBullet(const int additional_dx, const int additional_dy, int i);
void RefreshBullet(const int additional_dx, const int additional_dy, int i);

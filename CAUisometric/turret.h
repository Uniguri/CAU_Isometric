#pragma once

#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#include "constant_value.h"
#include "utility.h"
#include "bullet.h"

struct Turret
{
	ObjectID obj;
	SceneID scene;
	int x, y;
	int inner_x, inner_y;
	time_t fire_late;
	time_t last_fire_time;
	bool active = true;
};

void InitTurret();
void MoveTurret(const int dx, const int dy);

void TurretFire(const int dx, const int dy, int i);

bool isnearPlayer(const int dx, const int dy, int range, int i);

void isTurretHitted(int i);
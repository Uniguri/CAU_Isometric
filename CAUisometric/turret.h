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
};

void InitTurret(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], SceneID scene, int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int level);
void MoveTurret(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], const int dx, const int dy, const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int level);

void TurretFire(Turret* turret, Bullet* bullet);
bool IsHitted(Turret* turret, Bullet* bullet);
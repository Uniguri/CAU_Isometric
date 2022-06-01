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

void InitTurret();
void MoveTurret(const int dx, const int dy);

void TurretFire();
bool IsHitted();
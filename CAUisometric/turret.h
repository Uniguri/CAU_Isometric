#pragma once

#include <bangtal.h>

#include "constant_value.h"
#include "utility.h"
#include "bullet.h"

struct Turret
{
	ObjectID obj;
	SceneID scene;
	int x, y;
};

void InitTurret(Turret* turret, SceneID scene, const int x, const int y, const int inner_x, const int inner_y);
void TurretFire(Turret* turret, Bullet* bullet);
bool IsHitted(Turret* turret, Bullet* bullet);

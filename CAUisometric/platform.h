#pragma once
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#include "constant_value.h"
#include "utility.h"
#include "Player.h"

struct Door
{
	ObjectID obj;
	SceneID scene;
	int x, y;
	int inner_x, inner_y;
	bool active = false;
};

int CreateRandomMap(int height = 1, int width = 1, int ck = 0);
void MakeMap();
void MoveMap(int dx, int dy);
void MakeDoor();
void MoveDoor(const int dx, const int dy);
void ActiveDoor();
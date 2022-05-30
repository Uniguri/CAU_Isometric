#pragma once
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#include "constant_value.h"
#include "utility.h"

int CreateRandomMap(int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int level, int height = 1, int width = 1, int ck = 0);
void MakeMap(int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], const SceneID scene, const int level);
void MoveMap(ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], ObjectID scene, int level, int dx, int dy);
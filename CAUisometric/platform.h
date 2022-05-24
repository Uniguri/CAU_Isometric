#pragma once
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#include "constant_value.h"

struct pos {
	int n, m;
};

int CreateRandomMap(int base[MAX_LEVEL][baseN + 1][baseM + 1], int level, int height = 1, int width = 1, int ck = 0);
void ShowMap(int base[MAX_LEVEL][baseN + 1][baseM + 1], ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], SceneID scene, int level);
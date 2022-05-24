#pragma once
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 1
#define MAX_HEIGHT 300
#define MAX_WIDTH 300
#define CHUNK_SIZE 15
#define TILE_SIZE 50
#define scale 2.f
#define blockLimit 50
#define baseN 10
#define baseM 10

struct pos {
	int n, m;
};

int randomCreatePlatform(int base[MAX_LEVEL][baseN + 1][baseM + 1], int level, int height = 1, int width = 1, int ck = 0);
void printPlatform(int base[MAX_LEVEL][baseN + 1][baseM + 1], ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], SceneID scene, int level);
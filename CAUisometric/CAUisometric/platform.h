#pragma once
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#define L 1
#define N 300
#define M 300
#define block 15
#define size 50
#define scale 2.f
#define blockLimit 50
#define baseN 10
#define baseM 10

struct pos {
	int n, m;
};

void randomCreatePlatform(int l, int n, int m);
void printPlatform();
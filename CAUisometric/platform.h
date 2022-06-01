#pragma once
#include <bangtal.h>
#include <stdlib.h>
#include <time.h>

#include "constant_value.h"
#include "utility.h"

int CreateRandomMap(int height = 1, int width = 1, int ck = 0);
void MakeMap();
void MoveMap(int dx, int dy);
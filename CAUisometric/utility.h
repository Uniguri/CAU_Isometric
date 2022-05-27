#pragma once
#include <math.h>
#include "constant_value.h"
#include "types.h"

// 각 꼭짓점들은 순서대로 들어가야함.
bool IsCollision(const Coord target, const int number_of_points, const Coord* points);
bool IsCollision(const int target_x, const int target_y, const int number_of_points, const Coord* points);

Coord TransformCoord(const Coord original_coord, const int inner_x, const int inner_y, const int dx, const int dy);
Coord TransformCoord(const Coord original_coord, const int inner_x, const int inner_y, const Coord d_coord);
Coord TransformCoord(const Coord original_coord, const Coord inner_coord, const int dx, const int dy);
Coord TransformCoord(const Coord original_coord, const Coord inner_coord, const Coord d_coord);
Coord TransformCoord(const int x, const int y, const Coord inner_coord, const int dx, const int dy);
Coord TransformCoord(const int x, const int y, const int inner_x, const int inner_y, const int dx, const int dy);
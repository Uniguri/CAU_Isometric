#pragma once
#include "constant_value.h"
#include "types.h"

inline bool IsCollision(const int target_x, const int target_y, const Square square);
inline bool IsCollision(const int target_x, const int target_y, const Triangle triangle);
inline bool IsCollision(const int target_x, const int target_y, const ReverseTriangle r_triangle);

inline Coord TransformCoord(const Coord original_coord, const int inner_x, const int inner_y, const int dx, const int dy);
inline Coord TransformCoord(const Coord original_coord, const Coord inner_coord, const int dx, const int dy);
inline Coord TransformCoord(const int x, const int y, const Coord inner_coord, const int dx, const int dy);
inline Coord TransformCoord(const int x, const int y, const int inner_x, const int inner_y, const int dx, const int dy);
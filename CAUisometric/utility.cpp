#include "utility.h"

inline bool IsCollision(const int target_x, const int target_y, const Square square)
{
    return false;
}

inline bool IsCollision(const int target_x, const int target_y, const Triangle triangle)
{
    return false;
}

inline bool IsCollision(const int target_x, const int target_y, const ReverseTriangle r_triangle)
{
    return false;
}

inline Coord TransformCoord(const Coord original_coord, const int inner_x, const int inner_y, const int dx, const int dy)
{
    return TransformCoord(original_coord.x, original_coord.y, inner_x, inner_y, dx, dy);
}

inline Coord TransformCoord(const Coord original_coord, const Coord inner_coord, const int dx, const int dy)
{
    return TransformCoord(original_coord.x, original_coord.y, inner_coord.x, inner_coord.y, dx, dy);
}

inline Coord TransformCoord(const int x, const int y, const Coord inner_coord, const int dx, const int dy)
{
    return TransformCoord(x, y, inner_coord.x, inner_coord.y, dx, dy);
}

inline Coord TransformCoord(const int x, const int y, const int inner_x, const int inner_y, const int dx, const int dy)
{
    Coord ret;
    int ret_x = (-dx + ((x + y - 2) * CHUNK_SIZE + inner_x + inner_y - 1) * TILE_WIDTH) * SCALE / 2;
    int ret_y = (-dy + ((y - x + 1) * CHUNK_SIZE + inner_x - inner_y) * TILE_HEIGHT) * SCALE / 2;

    ret.x = ret_x;
    ret.y = ret_y;
    return ret;
}

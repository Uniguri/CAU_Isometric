#include "utility.h"



bool IsCollision(const Coord target, const int number_of_points, const Coord* points)
{
    int crosses = 0;

    for (int i = 0; i < number_of_points; ++i)
    {
        int j = (i + 1) % number_of_points;
        if ((points[i].y > target.y) != points[j].y > target.y)
        {
            double atX = (points[j].x - points[i].x) * (target.y - points[i].y) / (points[j].y - points[i].y) + points[i].x;
            if (target.x < atX)
                ++crosses;
        }
    }

    return crosses % 2 > 0;

    ////Using SAT
    //for (int i = 0; i < number_of_points; ++i)
    //{
    //    const Coord point1 = points[i];
    //    const Coord point2 = points[(i + 1)%number_of_points];
    //    const Vec2d target_vector = { target.x - point1.x, target.y - point1.y };
    //    const Vec2d direction_vector = { point2.x - point1.x, point2.y - point1.y };
    //    const double square_length_of_direction_vector = pow(direction_vector.x, 2) + pow(direction_vector.y, 2);

    //    // target_vector poject on direction_vector
    //    const double project_value = (target_vector.x * (direction_vector.x) + target_vector.y * (direction_vector.y)) / square_length_of_direction_vector;
    //    Vec2d projected_target_vector = { project_value * direction_vector.x, project_value * direction_vector.y };

    //    const double min_x = fmin(0, direction_vector.x), max_x = fmax(0, direction_vector.x);
    //    if (!(min_x < projected_target_vector.x && projected_target_vector.x < max_x))
    //        return false;

    //    const double min_y = fmin(0, direction_vector.y), max_y = fmax(0, direction_vector.y);
    //    if (!(min_y < projected_target_vector.y && projected_target_vector.y < max_y))
    //        return false;
    //}

    //return true;
}

bool IsCollision(const int target_x, const int target_y, const int number_of_points, const Coord* points)
{
    return IsCollision({target_x, target_y}, number_of_points, points);
}

inline Coord TransformCoord(const Coord original_coord, const int inner_x, const int inner_y, const int dx, const int dy)
{
    return TransformCoord(original_coord.x, original_coord.y, inner_x, inner_y, dx, dy);
}

Coord TransformCoord(const Coord original_coord, const int inner_x, const int inner_y, const Coord d_coord)
{
    return TransformCoord(original_coord.x, original_coord.y, inner_x, inner_y, d_coord.x, d_coord.y);
}

inline Coord TransformCoord(const Coord original_coord, const Coord inner_coord, const int dx, const int dy)
{
    return TransformCoord(original_coord.x, original_coord.y, inner_coord.x, inner_coord.y, dx, dy);
}

Coord TransformCoord(const Coord original_coord, const Coord inner_coord, const Coord d_coord)
{
    return TransformCoord(original_coord.x, original_coord.y, inner_coord.x, inner_coord.y, d_coord.x, d_coord.y);
}

inline Coord TransformCoord(const int x, const int y, const Coord inner_coord, const int dx, const int dy)
{
    return TransformCoord(x, y, inner_coord.x, inner_coord.y, dx, dy);
}

Coord TransformCoord(const int x, const int y, const int inner_x, const int inner_y, const int dx, const int dy)
{
    Coord ret = { 0 };
    int ret_x = (-dx + ((x + y - 2) * CHUNK_SIZE + inner_x + inner_y - 1) * TILE_WIDTH);
    int ret_y = (-dy + ((y - x + 1) * CHUNK_SIZE + inner_x - inner_y) * TILE_HEIGHT);

    ret.x = ret_x;
    ret.y = ret_y;
    return ret;
}

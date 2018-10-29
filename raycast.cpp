/*
raycast.cpp

/// Mettre license

*/

#include "raycast.h"

#include "level.h"
#include "tile.h"

#include <cmath>
#include <cassert>

namespace stero
{

HitResult cast_ray(const Ray &ray, const Level &map)
{
    assert(ray.pos.x >= 0 && ray.pos.y >= 0 &&
           ray.pos.x < map.tilemap.width() && ray.pos.y < map.tilemap.height());

    sf::Vector2i map_pos = (sf::Vector2i)ray.pos;

    assert(!map.tilemap[map_pos].present()); // check if we didn't cast a ray from a solid wall

    sf::Vector2f delta, init_pos_off, side_dist;
    sf::Vector2i step;
    step.x = (ray.dir.x < 0) ? -1 :  1;
    step.y = (ray.dir.y < 0) ?  1 : -1; // because when we look down, y increases since (0,0) is the top-left corner of the screen

    init_pos_off.x = (step.x == -1) ? ray.pos.x - map_pos.x : map_pos.x + 1 - ray.pos.x;
    init_pos_off.y = (step.y ==  1) ? ray.pos.y - map_pos.y : map_pos.y + 1 - ray.pos.y;

    // can return infinity, but it isn't a problem since in this case the DDA will only consider the correct axis
    delta.x = 1 / std::abs(ray.dir.y); // |1/a| <=> |1/(y/1)| <=> |1/y|
    delta.y = 1 / std::abs(ray.dir.x); // |a| <=> |1/x|

    side_dist = {init_pos_off.x * delta.x, init_pos_off.y * delta.y};

    Direction   vertical_side = (step.x ==  1) ? West  : East;
    Direction horizontal_side = (step.y ==  1) ? North : South;

    // perform DDA
    Direction hit_side;
    while (!map.tilemap[map_pos].present())
    {
        if (side_dist.x > side_dist.y)
        {
            side_dist.y += delta.y;
            map_pos.x += step.x;
            hit_side = vertical_side;
        }
        else
        {
            side_dist.x += delta.x;
            map_pos.y += step.y;
            hit_side = horizontal_side;
        }

        // Should never happen since maps are always closed
        assert(map_pos.x < map.tilemap.width() && map_pos.y < map.tilemap.height()
               && map_pos.x >= 0 && map_pos.y >= 0);
    }

    // at this point map_pos contains the position of the hit tile
    HitResult hit;
    hit.side = hit_side;
    hit.tile_pos = map_pos;
    if (vertical(hit_side))
    {
        hit.wall_pos = ray.pos.y + (side_dist.y-delta.y)*(-ray.dir.y);
    }
    else
    {
        hit.wall_pos = ray.pos.x + (side_dist.x-delta.x)*ray.dir.x;
    }
    hit.wall_pos -= std::floor(hit.wall_pos);

    assert(hit.wall_pos >= 0);

    return hit;
}

}

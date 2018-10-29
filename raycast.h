/*
raycast.h

/// Mettre license

*/
#ifndef RAYCAST_H
#define RAYCAST_H

#include <SFML/System/Vector2.hpp>

#include "direction.h"

namespace stero
{

struct Ray
{
    sf::Vector2f pos;
    sf::Vector2f dir;
};

struct HitResult
{
    sf::Vector2i tile_pos;
    float        wall_pos;
    Direction    side;
};

struct Level;

HitResult cast_ray(const Ray& ray, const Level& map);

}

#endif // RAYCAST_H

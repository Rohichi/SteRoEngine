/*
level.h

/// Mettre license
*/
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include <SFML/Graphics/Image.hpp>

#include "tilemap.h"

namespace stero
{

struct TileData;
struct Actor;
struct Level
{
    Tilemap tilemap;       // un array 2D qui contient un index dans la table de tuiles disponibles (-1 => non présent)

    std::vector<TileData>   tile_table; // une table qui contient toutes les tuiles différentes utilisées par la map

    sf::Image floor;
    sf::Image ceiling; // si on veut aussi un sol et un plafond texturés

    //std::vector<Actor> actors; // une liste des éléments, genres ennemis, sprites et leur position initiale sur la map
};

}

#endif // LEVEL_H

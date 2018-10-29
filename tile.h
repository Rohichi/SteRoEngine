/*
tile.h

/// Mettre license

*/
#ifndef TILE_H
#define TILE_H

#include "foursided.h"

#include <SFML/Graphics/Image.hpp>

namespace stero
{

struct TileData
{
    FourSided<sf::Image> textures;
};

struct Tile
{
    Tile() = default;
    Tile(unsigned in_idx)
        : idx(in_idx)
    {}

    unsigned idx { 0 };

    bool present() const
    {
        return idx != 0;
    }
};

}

#endif // TILE_H

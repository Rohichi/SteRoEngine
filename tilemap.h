/*
tilemap.h

/// Mettre license

*/
#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <initializer_list>
#include <cassert>

#include <SFML/System/Vector2.hpp>

#include "tile.h"

namespace stero
{

class Tilemap
{
public:
    Tilemap(size_t width, size_t height)
        : m_width(width), m_height(height), m_data(width*height)
    {}

    Tilemap(std::initializer_list<std::initializer_list<Tile>> list)
        : m_width(list.size() ? list.begin()->size() : 0), m_height(list.size()),
          m_data(m_width*m_height)
    {
        for (size_t i { 0 }; i < list.size(); ++i)
        {
            auto row = *(list.begin() + i);
            assert(row.size() == m_width);

            std::copy(row.begin(), row.end(), m_data.begin() + m_width*i);
        }
    }

    Tile& operator[](const sf::Vector2i& pos)
    {
        //assert(pos.x >= 0 && pos.y >= 0 && pos.x < m_width && pos.y < m_height);
        return m_data[pos.x + m_width*pos.y];
    }
    const Tile& operator[](const sf::Vector2i& pos) const
    {
        //assert(pos.x >= 0 && pos.y >= 0 && pos.x < m_width && pos.y < m_height);
        return m_data[pos.x + m_width*pos.y];
    }

    Tile& operator[](const sf::Vector2u& pos)
    {
        //assert(pos.x < m_width && pos.y < m_height);
        return m_data[pos.x + m_width*pos.y];
    }
    const Tile& operator[](const sf::Vector2u& pos) const
    {
        //assert(pos.x < m_width && pos.y < m_height);
        return m_data[pos.x + m_width*pos.y];
    }

    size_t  width() const { return m_width ; }
    size_t height() const { return m_height; }

private:
    size_t            m_width;
    size_t            m_height;
    std::vector<Tile> m_data;
};

}

#endif // TILEMAP_H

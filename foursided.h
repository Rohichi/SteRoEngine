/*
foursided.h

/// Mettre license

*/
#ifndef FOURSIDED_H
#define FOURSIDED_H

#include "direction.h"

namespace stero
{

template <typename T>
class FourSided
{
public:
    FourSided() = default;

    explicit FourSided(T t_data)
    { set(t_data); }

    void set(const T& t_data)
    {
        m_north = t_data;
        m_south = t_data;
        m_east = t_data;
        m_west = t_data;
    }

    T& operator[](Direction dir)
    {
        switch (dir)
        {
            case North:
                return m_north;
            case South:
                return m_south;
            case East:
                return m_east;
            case West:
                return m_west;
        }
    }
    const T& operator[](Direction dir) const
    {
        switch (dir)
        {
            case North:
                return m_north;
            case South:
                return m_south;
            case East:
                return m_east;
            case West:
                return m_west;
        }
    }

private:
    T m_north;
    T m_south;
    T m_west;
    T m_east;
};

}

#endif // FOURSIDED_H

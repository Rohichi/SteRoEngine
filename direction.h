/*
direction.h

/// Mettre license

*/
#ifndef DIRECTION_H
#define DIRECTION_H

#include <stdint.h>

namespace stero
{

enum Direction : int8_t
{
    North = 1, // this way the opposite direction can be found by doing -dir
    South = -North,
    West  = 2,
    East  = -West
};

inline bool horizontal(Direction dir)
{
    return dir & 0x1; // is odd ?
}
inline bool vertical(Direction dir)
{
    return (dir & 0x1) == 0; // is even ?
}

}

#endif // DIRECTION_H

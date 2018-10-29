/*
renderer.h

/// Mettre license

*/
#ifndef RENDERER_H
#define RENDERER_H

#include "level.h"
#include "camera.h"

namespace stero
{

void render(const Level& level, const Camera& cam, sf::Uint8* buffer, size_t width, size_t height);

}

#endif // RENDERER_H

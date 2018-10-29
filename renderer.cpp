/*
renderer.cpp

// Mettre license

*/

#include "renderer.h"

#include <cmath>
#include <cstring>
#include <iostream>

#include "raycast.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

namespace stero
{

void memsetl(void* dst , uint32_t val, size_t n)
{
    uint32_t* dst_ptr = (uint32_t*)dst;
    while (n--)
    {
        *dst_ptr++ = val;
    }
}

void draw_wall(const sf::Image& tex, sf::Uint32 *col_stripe, size_t col_height, int wall_off, size_t wall_height, float wall_x);

void render(const Level& level, const Camera& cam, sf::Uint8* buffer, size_t width, size_t height)
{
    std::swap(width, height); // flip the image's dimensions

//#pragma omp parallel for
    for (size_t scr_x = 0 ; scr_x < width; ++scr_x)
    {
        float cam_x = (2 * scr_x) / (float)width - 1.0;
        float ray_angle = cam_x * (cam.fov.x/2) + cam.alpha;

        Ray ray;
        ray.pos = cam.pos;
        sincosf(ray_angle, &ray.dir.y, &ray.dir.x);

        HitResult hit = cast_ray(ray, level);
        Tile tile = level.tilemap[hit.tile_pos];
        const sf::Image& texture = level.tile_table[tile.idx-1].textures[hit.side];

        sf::Vector2f corrected_pos = (sf::Vector2f)hit.tile_pos;
        corrected_pos.x += (hit.side == East ) ? 1 : 0;
        corrected_pos.y += (hit.side == South) ? 1 : 0;

        if (vertical(hit.side))
            corrected_pos.y += hit.wall_pos;
        else
            corrected_pos.x += hit.wall_pos;

        float actual_dist = std::hypot(corrected_pos.x - ray.pos.x, corrected_pos.y - ray.pos.y);

        float corrected_dist = actual_dist * cosf(cam_x * (cam.fov.x/2));

        size_t line_height = height / corrected_dist;

        int start = height/2 - line_height/2;

        // draw the ceil
        if (start > 0) memsetl(buffer + (scr_x*height)*4, 0xff00ff00, start);

        draw_wall(texture, (uint32_t*)buffer + scr_x*height, height, start, line_height, hit.wall_pos);

        // draw the floor
        if (start + line_height < height) memsetl(buffer + (scr_x*height + start + line_height)*4, 0xffff00ff, height - (start + line_height));
    }
}

void draw_wall(const sf::Image& tex, sf::Uint32* col_stripe, size_t col_height, int wall_off, size_t wall_height, float wall_x)
{
    //memsetl((uint8_t*)col_stripe + wall_off*4, 0xffffffff, wall_height);
    for (size_t i { 0 }; i < wall_height; ++i)
    {
        int scr_y = i+wall_off;
        if (scr_y >= 0 && scr_y < col_height)
        {
            float texX = wall_x*tex.getSize().x;
            float texY = (float)i / wall_height * tex.getSize().y;

            col_stripe[scr_y] = be32toh(tex.getPixel(texX, texY).toInteger());
        }
    }
}

}

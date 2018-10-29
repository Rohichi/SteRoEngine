#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdint>
#include <cmath>

#include "level.h"
#include "renderer.h"

int main(int argc, char** argv)
{
    using namespace stero;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");

    sf::Uint8* buffer = new sf::Uint8[window.getSize().x*window.getSize().y*4];

    sf::Image wall;
    wall.loadFromFile("data/greystone.png");

    std::vector<TileData> tile_table(1);
    tile_table[0] = TileData{FourSided{wall}};

    Level level {{
            {1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1},
            {1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1},
                 }, tile_table};

    float angle = 0;
    float fov = M_PI_2; // 90°
    Camera cam {{1.5, 2.4}, angle, {fov, fov}};

    for (size_t i { 0 }; i < 1; ++i)
    {
        render(level, cam, buffer, window.getSize().y, window.getSize().x);
    }

    sf::Texture text;
    text.create(window.getSize().y, window.getSize().x);
    sf::Sprite sprt;
    sprt.setTexture(text);
    sprt.setOrigin(sf::Vector2f(window.getSize().y, window.getSize().x)/2.f);
    sprt.setPosition((sf::Vector2f)window.getSize()/2.f);
    sprt.setRotation(90);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        text.update(buffer);

       // Now we start rendering to the window, clear it first
       window.clear();
       // Draw the texture
       window.draw(sprt);
       // End the current frame and display its contents on screen
       window.display();
    }

    return 0;

}

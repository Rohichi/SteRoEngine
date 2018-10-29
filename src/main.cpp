#include <stdio.h>

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int ac, char **av, char **env)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SteRoEngine");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            /** **** INPUT HANDLER **** **/
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    break;
                case sf::Event::KeyReleased:
                    break;
                default:
                    break;
            }
        }

        /** **** UPDATE ENGINE **** **/

        /** ****** AFFICHAGE ****** **/
        window.clear();

        window.display();
    }
    return (0);
}

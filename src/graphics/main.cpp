#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "Shapes.h"

using namespace std;
typedef unsigned int uint;


int main()
{
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.antialiasingLevel = 8;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);
    window.setActive();

    sf::View v(sf::FloatRect(0, 0, 640, 480));
    v.setViewport(sf::FloatRect(0, 0, 1, 1));
    window.setView(v);

//    sf::CircleShape c(2, 10);

    vector<float> xvec = make_random<float>(5000, 0, 20);
    vector<float> yvec = make_random<float>(5000, 0, 20);

//    std::sort(xvec.begin(), xvec.end());

    std::unique_ptr<GraphicItem> it = draw_points(xvec, yvec,
            {20.f, 20.f, window.getSize().x - 40.f, window.getSize().y - 40.f});

    it->set_color(sf::Color(100, 100, 255));

    std::cout << it->size() << std::endl;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key: exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            // Resize event: adjust the viewport
            if (event.type == sf::Event::Resized){
                v.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
            }
        }

        it->draw(window);

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}

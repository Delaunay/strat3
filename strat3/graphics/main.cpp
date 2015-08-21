#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <random>
#include <vector>
#include <cmath>

#include <iostream>

#include "Painter.h"

using namespace std;
typedef unsigned int uint;


template<typename T>
vector<T> make_random(size_t n, T min = 0, T max = 1)
{
//    std::mt19937 eng;   eng.seed(20);

//    std::uniform_real<T> r(min, max);


    vector<T> ref(n);
    for(auto& x : ref) x = std::rand(); //r(eng);
    return ref;
}

template<typename T>
vector<T> lin_space(size_t n, T min = 0, T max = 1)
{
    vector<T> ref(n);
    double dt = (max - min) / (n - 1.f);

    if (min > max)
        dt = (min - max) / (n - 1.f);

    for(int i = 0; i < n; ++i)
        ref[i] = min + i * dt;

    return ref;
}

namespace axes{
    struct X {};
    struct Y {};
}





template<typename T/*, typename T1*/>
struct Scale{
    Scale() = default;

    Scale(T min_, T max_):
        min(min_), max(max_)
    {
        if (min > max){
            max = min_;
            min = max_;
        }
    }

    T operator() (const T& val, sf::Uint32 width) { return x(val, width);   }

    T x(const T& val, sf::Uint32 width) {   return val * (width / (max - min) - min);   }
    T y(const T& val, sf::Uint32 height){   return height - val * height / (max - min); }

    T min{0};
    T max{1};
};


template<typename T>
void draw_line(const vector<T>& v, sf::RenderWindow& rw)
{
    Painter l;

    sf::Vector2f size = rw.getView().getSize();
    //sf::Vector2u size = rw.getSize();

    auto minmax = std::minmax_element(v.begin(), v.end());

    Scale<float> y((*minmax.first), (*minmax.second));
    Scale<float> x(0, v.size());

    sf::Vector2f p1 = {x.x(0, size.x), y.y(v[0], size.y)};
    sf::Vector2f p2;

    for(int i = 1, n = v.size(); i < n; i++)
    {
        p2 = {x.x(i, size.x), y.y(v[i], size.y)};

        rw.draw(l.line(p1, p2));

        p1 = p2;
    }
}


template<typename T>
void draw_line(const vector<T>& vx, const vector<T>& vy, sf::RenderWindow& rw)
{
    Painter l;

    sf::Vector2f size = rw.getView().getSize();
    //sf::Vector2u size = rw.getSize();

    auto xminmax = std::minmax_element(vx.begin(), vx.end());
    auto yminmax = std::minmax_element(vy.begin(), vy.end());

    Scale<float> x((*xminmax.first), (*xminmax.second));
    Scale<float> y((*yminmax.first), (*yminmax.second));

    sf::Vector2f p1 = {x.x(vx[0], size.x), y.y(vy[0], size.y)};
    sf::Vector2f p2;

    for(int i = 1, n = vx.size(); i < n; i++)
    {
        p2 = {x.x(vx[i], size.x), y.y(vy[i], size.y)};

        rw.draw(l.line(p1, p2));

        p1 = p2;
    }
}

int main()
{
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.antialiasingLevel = 8;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);
    window.setActive();

    sf::View v(sf::FloatRect(0, 0, 640, 480));
    v.setViewport(sf::FloatRect(0, 0, 1, 1));
    window.setView(v);

//    sf::CircleShape c(2, 10);

    vector<float> xvec = make_random<float>(50, 0, 20);
    vector<float> yvec = make_random<float>(50, 0, 20);

    std::sort(xvec.begin(), xvec.end());

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

        draw_line(xvec, yvec, window);

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}

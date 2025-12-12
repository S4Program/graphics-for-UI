#include <iostream>
#include "graphicsForUI/grid.h"
#include "graphicsForUI/button.h"
#include "graphicsForUI/defaultMenu.h"

int main()
{
    const sf::Vector2u screenResolution = {1000u, 1000u};

    auto window = sf::RenderWindow(sf::VideoMode(screenResolution), "Table example");
    window.setFramerateLimit(60);

    gui::DefaultMenu menu("default menu", {0,0}, sf::Vector2f(300,300), sf::Color(60,60,60), sf::Color(170, 100, 20), 20, &window);
    gui::Button b1(sf::Vector2f(50.f,50.f), sf::Color(200,200,200), sf::Color(100,100,100), sf::Color(0,0,0), &window, "First", 16);
    gui::Button b2(sf::Vector2f(50.f,50.f), sf::Color(200,200,200), sf::Color(100,100,100), sf::Color(0,0,0), &window, "Second", 16);
    gui::Button b3(sf::Vector2f(50.f,50.f), sf::Color(200,200,200), sf::Color(100,100,100), sf::Color(0,0,0), &window, "Third", 16);
    gui::Grid grid(sf::Vector2f(300,300), sf::Vector2f(3,3));

    b1.pack({0,0});
    b2.pack({0,0});
    b3.pack({0,0});

    grid.setElement({1,1},&b1);
    grid.setElement({2,2},&b2);
    grid.setElement({3,3},&b3);

    menu.addElement(&grid);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        menu.update(window.getView());
        grid.update();

        window.clear();
        window.draw(menu);
        window.display();
    }
}

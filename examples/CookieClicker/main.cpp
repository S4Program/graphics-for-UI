#include <iostream>
#include <SFML/Graphics.hpp>
#include "graphicsForUI/defaultMenu.h"
#include "graphicsForUI/labelElement.h"
#include "graphicsForUI/slider.h"

/*
        TO-DO:
        
    - Make a Group class for a mix of absolute and relative positioning
    - (Change how objects are being added to the menus (use of immediate UI?))
    - Implement a grid component
    - Implement a canvas system
    - Add more types of components (Colored tiles, etc.)
    - More example projects
    - Make code more readable (optional)
*/

int main()
{
    const sf::Vector2u screenResolution = {1000u, 1000u};

    auto window = sf::RenderWindow(sf::VideoMode(screenResolution), "Demo GUI project");
    window.setFramerateLimit(60);

    gui::Button button(sf::Vector2f(100,30), sf::Color(160,160,160), sf::Color(100,100,100), sf::Color(0,0,0), &window, "click here", 20.f);
    button.pack(sf::Vector2f(0,10));

    gui::DefaultMenu menu("default menu", {0,0}, sf::Vector2f(300,300), sf::Color(60,60,60), sf::Color(170, 100, 20), 20, &window);
    // menu.setPadding({50,0});

    gui::Label l1(20, sf::Color(255,255,255), "Clicker the game");
    gui::Label l2(20, sf::Color(255,255,255), "Clicks: 0");
    l1.pack(sf::Vector2f(0,0));
    l2.pack(sf::Vector2f(0,30));

    menu.addElement(&l1);
    menu.addElement(&l2);
    menu.addElement(&button);

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

        static int counter = 0;
        if(button.isClicked().first)
        {
            l2.setMessage("Clicks: "+std::to_string(++counter));
            printf("Clicked left mouse!\n");
        }
        window.clear();
        window.draw(menu);
        window.display();
    }
}

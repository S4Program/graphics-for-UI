#include <iostream>
#include <SFML/Graphics.hpp>
#include "graphicsForUI/defaultMenu.h"
#include "graphicsForUI/labelElement.h"
#include "graphicsForUI/slider.h"

/*
        TO-DO:
        
    - Make a Group class for a mix of absolute and relative positioning
    - Add more types of components
    - Try to use the pros of inheritance by 
    - Make buttons adapt to change in size
    - Make code more readable (optional)
*/

int main()
{
    const sf::Vector2u screenResolution = {1000u, 1000u};

    auto window = sf::RenderWindow(sf::VideoMode(screenResolution), "Demo GUI project");
    window.setFramerateLimit(60);

    gui::Button button(sf::Vector2f(100,30), sf::Color(160,160,160), sf::Color(100,100,100), sf::Color(0,0,0), &window, "click here", 20.f);
    gui::Slider slider(sf::Vector2f(0,100), 0, sf::Color(100,100,100), sf::Color(200,100,100), &window, sf::Vector2f(100,10));
    button.pack(sf::Vector2f(0,30));
    slider.pack(sf::Vector2f(0,30));

    gui::DefaultMenu menu("default menu", {0,0}, sf::Vector2f(300,300), sf::Color(60,60,60), sf::Color(170, 100, 20), 20, &window);
    // menu.setPadding({50,0});

    gui::Label l1(20, sf::Color(255,255,255), "Clicker the game");
    gui::Label l2(20, sf::Color(255,255,255), "Version: ALPHA");
    l1.pack(sf::Vector2f(0,10));
    l2.pack(sf::Vector2f(0,60));

    menu.addElement(&l1);
    menu.addElement(&l2);

    menu.addElement(&button);
    menu.addElement(&slider);
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

        if(button.isClicked().first)
        {
            printf("[main.cpp]Clicked left mouse\n");
        }
        window.clear();
        window.draw(menu);
        window.display();
    }
}

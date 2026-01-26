#include <iostream>
#include "graphicsForUI/grid.h"
#include "graphicsForUI/button.h"
#include "graphicsForUI/defaultMenu.h"

int main()
{
//--- Variables
    const sf::Vector2u screenResolution = {1000u, 1000u};
    const sf::Vector2f menuSize = {300.f, 400.f};

    auto window = sf::RenderWindow(sf::VideoMode(screenResolution), "Table example");
    window.setFramerateLimit(60);

    gui::DefaultMenu menu("default menu", {0,0}, menuSize, sf::Color(60,60,60), sf::Color(170, 100, 20), 20, &window);
    gui::Grid grid(menuSize, sf::Vector2i(3,4));
    gui::Button* buttons[10];
    
//--- Setting up grid
    for(int i=0; i<9; i++)
    {
        buttons[i] = new gui::Button(sf::Vector2f(75.f,75.f), sf::Color(200,200,200), sf::Color(0,0,0), &window, std::to_string(i), 40);
        grid.setElement({i%3, i/3},buttons[i]);
    }
    buttons[9] = new gui::Button(sf::Vector2f(75.f,75.f), sf::Color(200,200,200), sf::Color(0,0,0), &window, "9", 40);
    grid.setElement({1, 3},buttons[9]);

    menu.addElement(&grid);

//--- Main cycle
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        //--- Button update
        for(int i=0; i<10; i++){
            if(buttons[i]->isClicked(sf::Mouse::Button::Left)) {};
        }

        menu.update(window.getView());

        window.clear();
        window.draw(menu);
        window.display();
    }
}

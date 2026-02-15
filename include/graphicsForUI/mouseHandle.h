#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

namespace gui
{
class MouseHandle
{
private:
    sf::RectangleShape* hitbox;
    sf::RenderWindow* window;
    
    std::vector<bool> flags;
    std::vector<bool> values;
    bool calculatedCycle = false; // If all flag values have been calculated for the current cycle
public:
    sf::Vector2f getMousePos() { return (sf::Vector2f)sf::Mouse::getPosition(*window); };

    bool isPressed(sf::Mouse::Button button);
    bool isHovered();
    bool isClicked(sf::Mouse::Button button);

    void nextCycle();

    MouseHandle(sf::RenderWindow* window, sf::RectangleShape* hitbox);
    MouseHandle(sf::RenderWindow* window);
};
}
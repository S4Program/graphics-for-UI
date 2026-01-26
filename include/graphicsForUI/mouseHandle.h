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
    // bool flag1 = !false,
    //      flag2 = !false;
    std::vector<bool> flags;
public:
    sf::Vector2f getMousePos() { return (sf::Vector2f)sf::Mouse::getPosition(*window); };

    bool isPressed(sf::Mouse::Button button);
    bool isHovered();
    bool isClicked(sf::Mouse::Button button);

    MouseHandle(sf::RenderWindow* window, sf::RectangleShape* hitbox);
    MouseHandle(sf::RenderWindow* window);
};
}
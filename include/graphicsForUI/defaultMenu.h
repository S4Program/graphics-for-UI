#pragma once
#include "uiMenu.h"
#include "button.h"

namespace gui
{
class DefaultMenu : public UIMenu
{
public:
    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;

    virtual void update(sf::View camera);
    
    virtual void setSize(sf::Vector2f size);
    virtual void setMenuBoxSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

    DefaultMenu(std::string title, sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window, sf::Font* font = NULL);
    DefaultMenu(sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window);
protected:

//---UI Elements
    Button closeButton;
    Label title;
};
}
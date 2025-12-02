#pragma once
#include "mouseHandle.h"
#include "uiElement.h"
#include "labelElement.h"

namespace gui
{
class Button : public UIElement
{
public:
    sf::Vector2f getSize() { return box.getSize(); };
    sf::Vector2f getMousePos() { return mouseHandle.getMousePos(); };
    sf::Vector2f getPosition() { return box.getPosition(); };
    MouseHandle getMouseHandle() { return mouseHandle; }
    virtual int getType() { return gui::BUTTON; };

    std::pair<bool, bool> isClicked();
    bool isHovered();
    std::pair<bool, bool> isPressed();

    void onHoverEvent();
    void setFont(sf::Font *font);

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update();

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

    Button(sf::Vector2f size, sf::Color idleColor, sf::Color hoverColor, sf::Color textColor, sf::RenderWindow* window, std::string label, float characterSize, sf::Font* font = NULL);
    Button(sf::Vector2f size, sf::Color idleColor, sf::Color hoverColor, sf::RenderWindow* window);
protected:
    sf::RectangleShape box;

    MouseHandle mouseHandle;
    sf::Color hoverColor;
    sf::Color idleColor;

    gui::Label buttonLabel;
};
}
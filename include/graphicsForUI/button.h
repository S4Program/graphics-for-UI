#pragma once
#include "mouseHandle.h"
#include "uiElement.h"
#include "labelElement.h"

/*
    To-Do:
    - Text will wrap if width is too small
*/

namespace gui
{
class Button : public UIElement
{
public:
    sf::Vector2f getSize() { return UIElement::getSize(); };
    sf::Vector2f getMousePos() { return mouseHandle.getMousePos(); };
    sf::Vector2f getPosition() { return box.getPosition(); };
    MouseHandle getMouseHandle() { return mouseHandle; }
    virtual int getType() { return gui::BUTTON; };
    gui::Label& getLabel() { return buttonLabel; };
    sf::RectangleShape& getBox() { return box; };
    
    bool isClicked(sf::Mouse::Button button);
    bool isHovered();
    bool isPressed(sf::Mouse::Button button);
    
    void onHoverEvent();
    void setFont(sf::Font *font);
    
    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update();

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);
    virtual void setMessage(std::string message);
    virtual void setIdleColor(sf::Color color) { idleColor = color; hoverColor = getHoverColor(color); };
    virtual void setHoverColor(sf::Color color) { hoverColor = color; };

    Button(sf::Vector2f size, sf::Color idleColor, sf::Color textColor, sf::RenderWindow* window, std::string label, float characterSize, sf::Font* font = NULL);
    Button(sf::Vector2f size, sf::Color idleColor, sf::RenderWindow* window);
protected:
    sf::RectangleShape box;

    MouseHandle mouseHandle;
    sf::Color hoverColor;
    sf::Color idleColor;
    float hoverRatio = 0.6f;

    gui::Label buttonLabel;

    sf::Color getHoverColor(sf::Color color) { 
        float r = (float)color.r * hoverRatio;
        float g = (float)color.g * hoverRatio;
        float b = (float)color.b * hoverRatio;
        sf::Color newColor = sf::Color(r, g, b);
        return newColor; 
    };
};
}
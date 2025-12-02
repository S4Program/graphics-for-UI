#pragma once
#include "uiElement.h"
#include "button.h"

namespace gui
{
class Slider : public UIElement
{
public:
    virtual int getType() { return SLIDER; };
    float getValue() { return value; };

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update();
    virtual void pack(sf::Vector2f padding) override;

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

    Slider(sf::Vector2f range, float startValue, sf::Color backColor, sf::Color foreColor, sf::RenderWindow* window, sf::Vector2f size);
private:
    float value;
    bool isSelected = false;

    sf::Vector2f range;
    Button cursor;
    sf::RectangleShape background;
};
}
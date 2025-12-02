#include "graphicsForUI/slider.h"

void gui::Slider::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(background);
    window.draw(cursor);
}

void gui::Slider::pack(sf::Vector2f padding)
{
    UIElement::pack(padding);
    cursor.pack(padding);
}

void gui::Slider::setPosition(sf::Vector2f position)
{
    background.setPosition(position);
    cursor.setPosition(sf::Vector2f(position.x + value * size.x, position.y));
}

void gui::Slider::setSize(sf::Vector2f size)
{
    background.setSize(sf::Vector2f(size.x * (range.y-range.x), size.y));
    cursor.setSize(sf::Vector2f(size.y, size.y));
}

gui::Slider::Slider(sf::Vector2f range, float startValue, sf::Color backColor, sf::Color foreColor, sf::RenderWindow* window, sf::Vector2f size)
:
UIElement(size),
cursor(sf::Vector2f(size.y, size.y), foreColor, foreColor + sf::Color(100,100,100), window)
{
    background.setPosition(padding);
    background.setSize(size);
    background.setFillColor(backColor);

    value = startValue;

    this->range = range;
}

void gui::Slider::update()
{
    cursor.isHovered(); //updating the hover state

    cursor.setPosition(sf::Vector2f(background.getPosition().x + value * background.getSize().x / range.y, background.getPosition().y)); // setting cursor a position based on the value. This is done to combat disappearance after moving menu

    //--- if the slider is being pressed or the mouse has selected it previously
    if(cursor.isPressed().first || isSelected && cursor.getMouseHandle().isPressed().first)
    {
        isSelected = true; // if the mouse is being held

        //--- crazy math equations to properly set cursor
        cursor.setPosition(sf::Vector2(std::max(background.getPosition().x, std::min(background.getPosition().x + background.getSize().x, cursor.getMousePos().x)), cursor.getPosition().y));
        value = (cursor.getPosition().x - background.getPosition().x) / background.getSize().x * range.y;
    }
    else if(!cursor.getMouseHandle().isPressed().first)
    {
        isSelected = false;
    }
}
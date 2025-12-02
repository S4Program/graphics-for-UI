#include "graphicsForUI/groupElement.h"

gui::Group::Group(sf::Vector2f absolutePosition, UIElements elements)
:
UIElement(absolutePosition)
{
    this->elements = elements;
    this->setPosition(absolutePosition);
}

gui::Group::Group(sf::Vector2f absolutePosition)
:
UIElement(absolutePosition)
{
}

void gui::Group::setPosition(sf::Vector2f position)
{
    for(UIElement* element : elements)
    {
        element->setPosition(position - this->padding + element->getPadding());
    }
    
    this->padding = position;
}

void gui::Group::setSize(sf::Vector2f size)
{

}

void gui::Group::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    for(UIElement* element : elements)
    {
        window.draw(*element);
    }
}

void gui::Group::update()
{
    
}

void gui::Group::addElement(UIElement* element)
{
    elements.push_back(element);
    this->setPosition(this->padding);
}
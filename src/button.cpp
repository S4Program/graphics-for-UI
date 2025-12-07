#include "graphicsForUI/button.h"

std::pair<bool, bool> gui::Button::isClicked()
{
    isHovered();
    return mouseHandle.isClicked();
}

bool gui::Button::isHovered()
{
    if(mouseHandle.isHovered()) 
    {
        box.setFillColor(hoverColor);
    }
    else
    {
        box.setFillColor(idleColor);
    }

    return mouseHandle.isHovered();
}

std::pair<bool, bool> gui::Button::isPressed()
{
    return {mouseHandle.isPressed().first && isHovered(), mouseHandle.isPressed().first && isHovered()};
}

void gui::Button::onHoverEvent()
{
}

void gui::Button::setPosition(sf::Vector2f position)
{
    box.setPosition(position);
    buttonLabel.setPosition(position + buttonLabel.getPadding());
}

void gui::Button::setSize(sf::Vector2f size)
{
    this->size = size;
    box.setSize(size);
    buttonLabel.setSize(size);
}

void gui::Button::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(box);
    window.draw(buttonLabel);
}

void gui::Button::update()
{
}

gui::Button::Button(sf::Vector2f size, sf::Color idleColor, sf::Color hoverColor, sf::Color textColor, sf::RenderWindow* window, std::string label, float characterSize, sf::Font* font)
:
UIElement(size),
mouseHandle(window, &box),
hoverColor(hoverColor),
idleColor(idleColor),
buttonLabel(characterSize, textColor, label, font)
{
    buttonLabel.pack(sf::Vector2f((size.x - gui::Label(characterSize, textColor, label, font).getSize().x) * 0.5f, (size.y - gui::Label(characterSize, textColor, label, font).getSize().y) * 0.5f));
    box.setSize(size);
    box.setPosition(padding);
    box.setFillColor(idleColor);
}

gui::Button::Button(sf::Vector2f size, sf::Color idleColor, sf::Color hoverColor, sf::RenderWindow* window)
:
UIElement(size),
mouseHandle(window, &box),
hoverColor(hoverColor),
idleColor(idleColor),
buttonLabel()
{
    box.setSize(size);
    box.setPosition(padding);
    box.setFillColor(idleColor);
}
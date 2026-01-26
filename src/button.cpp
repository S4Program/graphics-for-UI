#include "graphicsForUI/button.h"

bool gui::Button::isClicked(sf::Mouse::Button button)
{
    isHovered();
    return mouseHandle.isClicked(button);
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

bool gui::Button::isPressed(sf::Mouse::Button button)
{
    return mouseHandle.isPressed(button);
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
    // buttonLabel.setSize(size);
    buttonLabel.pack(sf::Vector2f((size.x - buttonLabel.getSize().x) * 0.5f, (size.y - buttonLabel.getSize().y) * 0.5f)); // I literally forgot one bracket...
}

void gui::Button::setMessage(std::string message)
{
    buttonLabel.setMessage(message);
}

void gui::Button::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(box);
    window.draw(buttonLabel);
}

void gui::Button::update()
{
    isHovered();
}

gui::Button::Button(sf::Vector2f size, sf::Color idleColor, sf::Color textColor, sf::RenderWindow* window, std::string label, float characterSize, sf::Font* font)
:
UIElement(size),
mouseHandle(window, &box),
idleColor(idleColor),
buttonLabel(characterSize, textColor, label, font)
{
    hoverColor = getHoverColor(idleColor);
    buttonLabel.pack(sf::Vector2f((size.x - gui::Label(characterSize, textColor, label, font).getSize().x) * 0.5f, (size.y - gui::Label(characterSize, textColor, label, font).getSize().y) * 0.5f));
    box.setSize(size);
    box.setPosition(padding);
    box.setFillColor(idleColor);
}

gui::Button::Button(sf::Vector2f size, sf::Color idleColor, sf::RenderWindow* window)
:
UIElement(size),
mouseHandle(window, &box),
idleColor(idleColor),
buttonLabel()
{
    hoverColor = getHoverColor(idleColor);
    box.setSize(size);
    box.setPosition(padding);
    box.setFillColor(idleColor);
}
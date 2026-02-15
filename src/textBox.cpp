#include "graphicsForUI/textBox.h"

void gui::TextBox::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(box);
    window.draw(text);
}

void gui::TextBox::setSize(sf::Vector2f size)
{
    box.setSize(size);
    text.setSize(size);
}

void gui::TextBox::setPosition(sf::Vector2f position)
{
    box.setPosition(position);
    text.setPosition
    (
        sf::Vector2f(position.x, text.getSize().y/2.f + position.y)
    );
}

void gui::TextBox::update()
{
    
}

void gui::TextBox::getEvent(std::optional<sf::Event> event)
{
    if(isFocused && event->is<sf::Event::TextEntered>())
    {
        inputLogic(event->getIf<sf::Event::TextEntered>()->unicode);
    }
}

void gui::TextBox::inputLogic(int charTyped)
{

    if(!(charTyped >= 32 && charTyped <= 127 || charTyped == _DELETE || charTyped == ENTER || charTyped == ESCAPE))
    {
        return;
    }

    if(charTyped != _DELETE && charTyped != ENTER && charTyped != ESCAPE && textValue.size() < characterLimit)
    {
        textValue.push_back(charTyped);
    }
    else if(charTyped == _DELETE && textValue.size() > 0)
    {
        textValue.pop_back();
    }
    else if(charTyped == ENTER)
    {
        isFocused = false;
        isSet = true;
    }

    text.setMessage(textValue);
}


gui::TextBox::TextBox(sf::RenderWindow* window, sf::Vector2f size, sf::Color boxColor, sf::Color foreColor, sf::Font* font, float characterSize, std::string defaultMessage, sf::Vector2f position, uint8_t characterLimit)
:
window(window),
box(size),
text(characterSize, foreColor, "...", font),
boxFrame(window, &box),
defaultMessage(defaultMessage),
characterLimit(characterLimit)
{
    box.setFillColor(boxColor);

    text.setPosition
    (
        sf::Vector2f(box.getPosition().x + box.getSize().x / 2 - 6*text.getText().getLocalBounds().size.x/2, box.getPosition().y + box.getSize().y / 2 - 12*text.getText().getLocalBounds().size.y / 2)
    );
}
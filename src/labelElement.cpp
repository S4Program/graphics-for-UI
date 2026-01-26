#include "graphicsForUI/labelElement.h"
bool gui::Label::loadedFont = false;
sf::Font gui::Label::defaultFont = sf::Font();

void gui::Label::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(backBox);
    window.draw(text);
} 

void gui::Label::setPosition(sf::Vector2f position)
{
    text.setPosition(position);
    backBox.setPosition(text.getGlobalBounds().position);
}

void gui::Label::setSize(sf::Vector2f size)
{
    text.setCharacterSize(text.getCharacterSize() / backBox.getSize().x * size.x);
    backBox.setSize(text.getGlobalBounds().size + text.getLocalBounds().position);
}

void gui::Label::setMessage(std::string message)
{
    this->text.setString(message);
}

sf::Font gui::Label::loadDefaultFont()
{
    if(loadedFont == false)
    {
        if(!defaultFont.openFromFile(defaultFontFilePath)) {}
        loadedFont = true;
    }
    assert(loadedFont != false);
    return defaultFont;
}

gui::Label::Label(float characterSize, sf::Color textColor, sf::Color backColor, std::string message, sf::Font* font)
:
UIElement(sf::Vector2f(characterSize * message.size(), characterSize)),
myFont(font == NULL ? loadDefaultFont() : *font),
text(myFont, message, characterSize)
{
//--- Text Setup
    text.setFillColor(textColor);
    text.setPosition(padding);

//--- Background Box Setup
    backBox = sf::RectangleShape
    (text.getGlobalBounds().size + text.getLocalBounds().position);
    backBox.setPosition(text.getGlobalBounds().position);
    backBox.setFillColor(backColor);
}

gui::Label::Label(float characterSize, sf::Color textColor, std::string message, sf::Font* font)
:
UIElement(sf::Vector2f(characterSize * message.size(), characterSize)),
myFont(font == NULL ? loadDefaultFont() : *font),
text(myFont, message, characterSize)
{
//--- Text Setup
    text.setFillColor(textColor);
    text.setPosition(padding);

//--- Background Box Setup
    backBox = sf::RectangleShape
    (text.getGlobalBounds().size + text.getLocalBounds().position);
    backBox.setPosition(text.getLocalBounds().position);
    backBox.setFillColor(sf::Color::Transparent);
}

gui::Label::Label(sf::Vector2f originSize, sf::Vector2f originPosition, float characterSize, sf::Color textColor, std::string message, sf::Font* font)
:
UIElement(sf::Vector2f(characterSize * message.size(), characterSize)),
myFont(font == NULL ? loadDefaultFont() : *font),
text(myFont, message, characterSize)
{
//--- Element Setup
    gui::UIElement::pack(sf::Vector2f((size.x - gui::Label(characterSize, textColor, message, font).getSize().x) * 0.5f, (size.y - gui::Label(characterSize, textColor, message, font).getSize().y) * 0.5f));

//--- Text Setup
    text.setFillColor(textColor);
    text.setPosition(sf::Vector2f((size.x - gui::Label(characterSize, textColor, message, font).getSize().x) * 0.5f, (size.y - gui::Label(characterSize, textColor, message, font).getSize().y) * 0.5f));

//--- Background Box Setup
    backBox = sf::RectangleShape
    (text.getGlobalBounds().size + text.getLocalBounds().position);
    backBox.setPosition(text.getLocalBounds().position);
    backBox.setFillColor(sf::Color::Transparent);
}

gui::Label::Label()
:
UIElement(sf::Vector2f(0,0), sf::Vector2f(0,0)),
myFont(loadDefaultFont()),
text(myFont)
{
    
}
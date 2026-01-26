#pragma once
#include "uiElement.h"

namespace gui
{
class Label : public gui::UIElement
{
private:
    std::string defaultFontFilePath = "..\\..\\include\\graphicsForUI\\resources\\fonts\\ARIAL.TTF";
    static sf::Font defaultFont;
    static bool loadedFont;
    sf::Font loadDefaultFont();
public:
    sf::Text& getText() { return text; };
    virtual sf::Vector2f getSize() { return backBox.getSize(); };
    virtual sf::Vector2f getPosition() { return backBox.getPosition(); };
    virtual int getType() { return gui::LABEL; };

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update() {};

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);
    void setMessage(std::string message);

    Label(float characterSize, sf::Color textColor, sf::Color backColor, std::string message, sf::Font* font = NULL);
    Label(float characterSize, sf::Color textColor, std::string message, sf::Font* font = NULL);
    Label(sf::Vector2f originSize, sf::Vector2f originPosition, float characterSize, sf::Color textColor, std::string message, sf::Font* font = NULL);
    Label();
protected:
    sf::Font myFont;
    sf::Text text;
    sf::RectangleShape backBox;
};
}
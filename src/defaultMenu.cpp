#include "graphicsForUI/defaultMenu.h"

void gui::DefaultMenu::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    if(!isVisible) return;

    window.draw(outlineBox);
    window.draw(title);
    window.draw(closeButton);
    window.draw(box);

    for(const UIElement* element : elements)
    {
        if(element->isVisible())
        {
            window.draw(*element);
        }
    }
}

void gui::DefaultMenu::update(sf::View camera)
{
    if(!isVisible) return;

//--- Updating Menu perspective relative to View
    // sf::Vector2f mousePos = outlineMouseHandle.getMousePos();
    // setSize( sf::Vector2f(size.x / startFOV.x * camera.getSize().x, size.y / startFOV.y * camera.getSize().y) );
    // setPosition( sf::Vector2f(position.x / startFOV.x * camera.getSize().x + camera.getCenter().x, position.y / startFOV.y * camera.getSize().y + camera.getCenter().y) );

//--- Menu's events
    UIMenu::outlineMouseEvent();
    UIMenu::inputEvent();    

    if(closeButton.isClicked(sf::Mouse::Button::Left)) // If the menu was closed by a button
    {
        isVisible = false;
        printf("[defaultMenu.cpp] Closed menu by a button\n");
    }

    
}

void gui::DefaultMenu::setSize(sf::Vector2f size)
{
    for(UIElement* element : elements)
    {
        element->setSize(sf::Vector2f(box.getSize().x / size.x * element->getSize().x, box.getSize().y / size.y * element->getSize().y));
    }

    this->setMenuBoxSize(size);
}

void gui::DefaultMenu::setMenuBoxSize(sf::Vector2f size)
{
    // printf("[defaultMenu.cpp] New menu size: %f, %f\n",size.x, size.y);
    
    //--- Updating relative menu box position for the top bar
    outlineBox.setSize(sf::Vector2f(size.x, outlineBox.getSize().y));
    closeButton.setPosition(sf::Vector2f(box.getPosition().x + outlineBox.getSize().x - closeButton.getSize().y, closeButton.getPosition().y));
    box.setSize(size);
    this->size = size;

    //--- To move elements too
    this->resetComponents(); 
}

void gui::DefaultMenu::setPosition(sf::Vector2f position)
{
    box.setPosition(sf::Vector2f(position.x, position.y + outlineThickness) );
    outlineBox.setPosition(position);
    title.setPosition(sf::Vector2f((outlineBox.getSize().x - title.getSize().x)*0.5f + position.x, position.y));
    closeButton.setPosition(sf::Vector2f(position.x + size.x - outlineThickness, position.y));

    gui::UIMenu::resetComponents();
}

//--- Menu with title and close button
gui::DefaultMenu::DefaultMenu(std::string title, sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float characterSize, sf::RenderWindow* window, sf::Font* font) 
: 
UIMenu(size, position, boxColor, outlineColor, Label(characterSize, sf::Color::White, title, font).getSize().y * 1.1f, window),
closeButton(sf::Vector2f(outlineThickness, outlineThickness), sf::Color(255,10,10), sf::Color(0,0,0), window, "X", outlineThickness, font),
title(characterSize, sf::Color::White, title, font)
{
    closeButton.setPosition(sf::Vector2f(position.x + size.x - outlineThickness, size.y));
    this->title.setPosition(sf::Vector2f((outlineBox.getSize().x - this->title.getSize().x)*0.5f + UIMenu::position.x, UIMenu::position.y));
}

//--- Menu with close button
gui::DefaultMenu::DefaultMenu(sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window) 
: 
UIMenu(size, position, boxColor, outlineColor, outlineThickness, window),
closeButton(sf::Vector2f(outlineThickness, outlineThickness), sf::Color(255,10,10), window)
{
    closeButton.pack(sf::Vector2f(position.x + size.x - outlineThickness, size.y));
}
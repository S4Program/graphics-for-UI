#include "graphicsForUI/defaultMenu.h"

void gui::DefaultMenu::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    if(!isVisible) return;

    window.draw(outlineBox);
    window.draw(closeButton);
    window.draw(box);

    for(const UIElement* element : elements)
    {
        window.draw(*element);
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

    if(closeButton.isClicked().first) // If the menu was closed by a button
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
    printf("[defaultMenu.cpp] New menu size: %f, %f\n",size.x, size.y);
    
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
    closeButton.setPosition(sf::Vector2f(position.x + size.x - outlineThickness, position.y));

    gui::UIMenu::resetComponents();
}

gui::DefaultMenu::DefaultMenu(std::string title, sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window, sf::Font* font) 
: 
UIMenu(size, position, boxColor, outlineColor, outlineThickness, window),
closeButton(sf::Vector2f(outlineThickness, outlineThickness), sf::Color(255,10,10), sf::Color(120,0,0), sf::Color(0,0,0), window, "X", outlineThickness, font) //<---LEFT HERE
// So basically I need a folder of default fonts set up, to easily be able to use them. Additionally the people are gonna be so thankful, yaaay
//title()
{
    closeButton.pack(sf::Vector2f(position.x + size.x - outlineThickness, size.y));
}

gui::DefaultMenu::DefaultMenu(sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window) 
: 
UIMenu(size, position, boxColor, outlineColor, outlineThickness, window),
closeButton(sf::Vector2f(outlineThickness, outlineThickness), sf::Color(255,10,10), sf::Color(120,0,0), window)
{
    closeButton.pack(sf::Vector2f(position.x + size.x - outlineThickness, size.y));
}
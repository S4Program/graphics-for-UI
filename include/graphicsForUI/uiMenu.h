#pragma once
#include "SFML/Graphics.hpp"
#include "uiElement.h"
#include "mouseHandle.h"

#include <vector>
#include <cassert>
#include <algorithm>

namespace gui
{   

class UIMenu : public sf::Drawable
{
public:
    virtual sf::Vector2f getPosition() { return position; };

    virtual void toggle(bool arg);
    virtual void outlineMouseEvent();
    virtual void inputEvent();

    virtual void recomputeSize();
    virtual void resetComponents();
    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const = 0;
    virtual void update(sf::View camera) = 0; //making this pure virtual because there are different types of menus

    virtual void addElement(UIElement* element);
    virtual void removeElement(int index);

    virtual void setSize(sf::Vector2f size) = 0; // for both menu and its elements
    virtual void setMenuBoxSize(sf::Vector2f size) = 0; // only for menu box
    virtual void setPosition(sf::Vector2f position) = 0;
    virtual void setPadding(sf::Vector2f padding);

    UIMenu(sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window);
protected:
typedef std::vector<gui::UIElement*> UIElements;
    UIElements elements;
    
    std::vector<int> inputTypes = {BUTTON, SLIDER, GRID}; // element types that will be processed in update function

//--- Box variables
    sf::RectangleShape box;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f padding = {0,0};

//--- Top bar variables
    sf::RectangleShape outlineBox;
    MouseHandle outlineMouseHandle;
    float outlineThickness;

//--- States
    bool isVisible = true;
    bool isMenuSelected = false;

//--- Additional dependencies
    sf::Vector2f previousMousePos;
    sf::Vector2f startFOV;
};

}

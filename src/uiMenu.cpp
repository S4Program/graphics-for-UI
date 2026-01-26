#include "graphicsForUI/uiMenu.h"

void gui::UIMenu::toggle(bool arg)
{
    isVisible = arg;
}

void gui::UIMenu::outlineMouseEvent()
{
    if(isMenuSelected)
    {
        setPosition(outlineBox.getPosition() + outlineMouseHandle.getMousePos() - previousMousePos);
    }

    if(outlineMouseHandle.isClicked(sf::Mouse::Button::Left) || outlineMouseHandle.isPressed(sf::Mouse::Button::Left) && isMenuSelected)
    {
        previousMousePos = outlineMouseHandle.getMousePos();
        isMenuSelected = true;
    }
    else 
    {
        isMenuSelected = false;
    }
}

void gui::UIMenu::inputEvent()
{
    for(UIElement* uiElement : elements)
    {
        //--- If current element's type is legible for an update 
        if(std::find(inputTypes.begin(), inputTypes.end(), uiElement->getType()) != inputTypes.end()) 
        {
            uiElement->update();
        }
    }
}

void gui::UIMenu::setPadding(sf::Vector2f padding)
{
    this->padding = padding;
}

void gui::UIMenu::recomputeSize()
{
    sf::Vector2f minimumSize = size;
    sf::Vector2f currentElementPosition = this->padding;
    for(UIElement* elem : elements)
    {
        // printf("x: %f\n", elem->getPadding().x + elem->getSize().x);
        if(elem->getPadding().x != 0)
        {
            currentElementPosition += sf::Vector2f(elem->getPadding().x + elem->getSize().x, 0);
        }
        else
        {
            currentElementPosition.x = std::max(currentElementPosition.x, elem->getSize().x + this->padding.x);
            minimumSize.x = std::max(minimumSize.x, elem->getSize().x);
        }
        if(elem->getPadding().y != 0)
        {
            currentElementPosition += sf::Vector2f(0, elem->getPadding().y + elem->getSize().y);
        }
        else
        {
            currentElementPosition.y = std::max(currentElementPosition.y, elem->getSize().y + this->padding.y);
            minimumSize.y = std::max(minimumSize.y, elem->getSize().y);
        }
        // printf("preMaxY: %f, currentElemPosition: %f\n", minimumSize.y, currentElementPosition.y);
        minimumSize = { std::max(minimumSize.x, currentElementPosition.x + this->padding.x), std::max(minimumSize.y, currentElementPosition.y + this->padding.y) };
        // printf("postMaxY: %f\n", minimumSize.y);
    }
    this->setMenuBoxSize(minimumSize);
}

void gui::UIMenu::resetComponents()
{
//--- Relative positioning

    sf::Vector2f previousPosition = box.getPosition() + this->padding; // setting up the variable for the first element

    int index = 0;
    for(UIElement* element : elements)
    {
        if(element->getPadding().y != 0)
        {
            previousPosition += sf::Vector2f(0, element->getPadding().y + (index != 0 ? elements.at(index-1)->getSize().y : 0)); // moving it lower than the previous element
        }

        if(element->getPadding().x != 0)
        {
            previousPosition += sf::Vector2f(element->getPadding().x + (index != 0 ? elements.at(index-1)->getSize().x : 0), 0);
        }

        element->setPosition(previousPosition);

        index++;
    } 
}

void gui::UIMenu::addElement(UIElement* element)
{
    elements.push_back(element);
    setPosition(outlineBox.getPosition()); //as the box represents the main frame, it can be used for getting the position...
    
    this->recomputeSize();
}

void gui::UIMenu::removeElement(int index)
{
    assert(index >= 0 && index < elements.size());
    elements.erase(elements.begin() + index);

    this->recomputeSize();
}

gui::UIMenu::UIMenu(sf::Vector2f size, sf::Vector2f position, sf::Color boxColor, sf::Color outlineColor, float outlineThickness, sf::RenderWindow* window)
:
startFOV(window->getView().getSize()),
size(size),
position(position),
outlineThickness(outlineThickness),
outlineMouseHandle(window, &outlineBox)
{
    box.setSize(size);
    box.setPosition(sf::Vector2f(position.x, position.y + outlineThickness) );
    box.setFillColor(boxColor);

    outlineBox.setPosition(position);
    outlineBox.setFillColor(outlineColor);
    outlineBox.setSize(sf::Vector2f(size.x, outlineThickness));
}

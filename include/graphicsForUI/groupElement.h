#pragma once
#include "uiElement.h"
#include <vector>

namespace gui
{
class Group : public gui::UIElement
{
private:
typedef std::vector<UIElement*> UIElements;
    UIElements elements;

public:
    virtual int getType() { return gui::GROUP; };

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update();

    void addElement(UIElement* element);

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);

    Group(sf::Vector2f absolutePosition);
    Group(sf::Vector2f absolutePosition, UIElements elements);
};
}
#include "graphicsForUI/mouseHandle.h"

bool gui::MouseHandle::isHovered()
{
    assert(hitbox != NULL);
    return hitbox->getGlobalBounds().contains(getMousePos());
}

bool gui::MouseHandle::isPressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}

bool gui::MouseHandle::isClicked(sf::Mouse::Button button)
{
    // bool res1 = isHovered() && isPressed().first && flag1,
    //      res2 = isHovered() && isPressed().second && flag2;
    
    // if(isPressed().first) flag1 = false;
    // else flag1 = true;
    // if(isPressed().second) flag2 = false;
    // else flag2 = true;

    // return {res1, res2};

// OLD                                                        
//------------------------------------------------------------
// NEW                 

    bool res = isHovered() && isPressed(button) && flags[(int)button];

    if(isPressed(button)) flags[(int)button] = false;
    else flags[(int)button] = true;

    return res;
}

gui::MouseHandle::MouseHandle(sf::RenderWindow* window, sf::RectangleShape* hitbox)
:
window(window),
hitbox(hitbox),
flags(std::vector<bool>(5,true))
{
    
}

gui::MouseHandle::MouseHandle(sf::RenderWindow* window)
:
window(window),
flags(std::vector<bool>(5,true))
{
    
}
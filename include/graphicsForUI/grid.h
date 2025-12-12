#pragma once
#include "uiElement.h"

namespace gui
{
class Grid : public UIElement
{

struct Cell
{
    UIElement* element;
    sf::Vector2f coords;
    void setPosition(sf::Vector2f position)
    {
        if(element != NULL)
        {
            element->setPosition(position);
        }
    }
};
public:
    public:
    virtual int getType() { return gui::GRID; };
    UIElement* getElement(int x, int y) { return cells[y][x].element; };
    UIElement* getConstElement(int x, int y) const { return cells[y][x].element; };

    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    virtual void update();

    virtual void setSize(sf::Vector2f size);
    virtual void setPosition(sf::Vector2f position);
    void resetComponents();

    void clearGrid();
    void initGrid();
    void setElement(sf::Vector2f coords, UIElement* element);

    Grid(sf::Vector2f gridSize, sf::Vector2f gridResolution);
    Grid(sf::Vector2f cellSize, sf::Vector2f gridResolution, bool flag);

private:
    //--- Starting Point
    sf::Vector2f origin;
    
    //--- Grid Parameters
    sf::Vector2f cellSize;
    sf::Vector2f gridResolution;
    std::vector<std::vector<Cell>> cells;

    /*
        This is how cells array looks like
        +------->
        |     + X
        |
        | +
        V Y
    */

};

}
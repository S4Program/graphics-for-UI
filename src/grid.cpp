#include "graphicsForUI/grid.h"

void gui::Grid::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    for(int y = 0; y < gridResolution.y; y++)
    {
        for(int x = 0; x < gridResolution.x; x++)
        {
            if(this->getConstElement(x,y) != NULL)
            {
                window.draw(*this->getConstElement(x,y));
            }
        }
    }
}

void gui::Grid::update()
{
    
}

void gui::Grid::setSize(sf::Vector2f size)
{
    this->cellSize = {this->cellSize.x / this->size.x * size.x, this->cellSize.y / this->size.y * size.y};
    this->size = size;

    for(int y = 0; y < gridResolution.y; y++)
    {
        for(int x = 0; x < gridResolution.x; x++)
        {
            // Changed indexation from x+1, y+1
            this->setElement({x,y}, this->getElement(x,y));
        }
    }
}
    
void gui::Grid::setPosition(sf::Vector2f position)
{
    this->origin = position;
    this->resetComponents();
}

void gui::Grid::resetComponents()
{
    sf::Vector2f currentPosition = origin;
    for(int y=0; y<gridResolution.y; y++)
    {
        for(int x=0; x<gridResolution.x; x++)
        {
            Cell* cell = &cells[y][x];

            if(cell->element != NULL)
            {
                float prevPositionX = currentPosition.x;
                currentPosition += (cellSize - cell->element->getSize()) / 2.f;
                cell->setPosition(currentPosition);
                currentPosition.x = prevPositionX + cellSize.x;
                currentPosition.y = y*cellSize.y + origin.y;
            }
            else
            {
                currentPosition.x += this->cellSize.x;
            }
        }
        currentPosition.x = origin.x;
        currentPosition.y += this->cellSize.y;
    }
}

void gui::Grid::clearGrid()
{
    for(std::vector<Cell>& cellRow : cells)
    {
        cellRow.clear();
    }
    cells.clear();
}

void gui::Grid::initGrid()
{
    for(int row=0; row<gridResolution.y; row++)
    {
        cells.push_back(std::vector<Cell>(gridResolution.x));
    }
}

void gui::Grid::setElement(sf::Vector2i coords, UIElement* element)
{
    assert(coords.x >= 0 && coords.x < gridResolution.x
        && coords.y >= 0 && coords.y < gridResolution.y 
        && "Index out of bounds");
    
    cells[coords.y][coords.x].element = element;
    cells[coords.y][coords.x].element->setSize({std::min(cellSize.x, element->getSize().x), std::min(cellSize.y, element->getSize().y)});
}

gui::Grid::Grid(sf::Vector2f gridSize, sf::Vector2i gridResolution)
:
UIElement(gridSize),
gridResolution(gridResolution),
cellSize({gridSize.x / gridResolution.x, gridSize.y / gridResolution.y})
{
    this->initGrid();
}
gui::Grid::Grid(sf::Vector2f cellSize, sf::Vector2i gridResolution, bool flag)
:
UIElement({cellSize.x * gridResolution.x, cellSize.y * gridResolution.y}),
gridResolution(gridResolution),
cellSize(cellSize)
{
    this->initGrid();
}
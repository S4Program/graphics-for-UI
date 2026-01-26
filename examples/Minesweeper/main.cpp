#include <iostream>
#include <random>
#include "graphicsForUI/grid.h"
#include "graphicsForUI/button.h"
#include "graphicsForUI/defaultMenu.h"

#define MAX_SEED 500000

bool generated_map = false;

struct Tile
{
    gui::Button* button;
    int state = 0;
    // 0 - hidden
    // 1 - unmasked
    // 2 - flagged

    int value = 0;
    // -1 - bomb
    // 1...9 - numbers

    sf::Color color;
};

sf::Color valueColors[] = {
    sf::Color::Blue, // blue
    sf::Color(0, 189, 173), //cyan
    sf::Color(5, 153, 0), // green
    sf::Color(184, 181, 0), //yellow
    sf::Color(224, 82, 0), //brown
    sf::Color(255, 43, 43), // light red
    sf::Color::Red, //red
    sf::Color::Red //red
};

void showCell(std::vector<std::vector<Tile>>& tiles, sf::Vector2i coords)
{
    tiles[coords.x][coords.y].button->setIdleColor(sf::Color(230,230,230));
    tiles[coords.x][coords.y].button->setMessage((tiles[coords.x][coords.y].value==0 ? " " : std::to_string(tiles[coords.x][coords.y].value)));
    tiles[coords.x][coords.y].state = 1;
}

void showEmptyArea(std::vector<std::vector<Tile>>& tiles, sf::Vector2i coords, sf::Vector2i gridSize, int distance)
{
    if(tiles[coords.x][coords.y].value == 0) distance = 0;
    if(distance > 1) return;

    showCell(tiles, coords);
    if(coords.x > 0 && tiles[coords.x-1][coords.y].state == 0) showEmptyArea(tiles,{coords.x-1,coords.y},gridSize,distance+1);
    if(coords.y > 0 && tiles[coords.x][coords.y-1].state == 0) showEmptyArea(tiles,{coords.x,coords.y-1},gridSize,distance+1);
    if(coords.x+1 < gridSize.y && tiles[coords.x+1][coords.y].state == 0) showEmptyArea(tiles,{coords.x+1,coords.y},gridSize,distance+1);
    if(coords.y+1 < gridSize.x && tiles[coords.x][coords.y+1].state == 0) showEmptyArea(tiles,{coords.x,coords.y+1},gridSize,distance+1);

    if(coords.y+1 < gridSize.x && coords.x+1 < gridSize.y && tiles[coords.x+1][coords.y+1].state == 0) showEmptyArea(tiles,{coords.x+1,coords.y+1},gridSize,distance+1);
    if(coords.y > 0 && coords.x+1 < gridSize.y && tiles[coords.x+1][coords.y-1].state == 0) showEmptyArea(tiles,{coords.x+1,coords.y-1},gridSize,distance+1);
    if(coords.y+1 < gridSize.x && coords.x > 0 && tiles[coords.x-1][coords.y+1].state == 0) showEmptyArea(tiles,{coords.x-1,coords.y+1},gridSize,distance+1);
    if(coords.y > 0 && coords.x > 0 && tiles[coords.x-1][coords.y-1].state == 0) showEmptyArea(tiles,{coords.x-1,coords.y-1},gridSize,distance+1);
}

void createMapValues(std::vector<std::vector<Tile>>& tiles, sf::Vector2i gridSize)
{
    for(int i=0; i<gridSize.y; i++)
    {
        for(int j=0; j<gridSize.x; j++)
        {
            //--- Set defaults
            // tiles[i][j].button->setMessage("");
            tiles[i][j].value = 0;
            tiles[i][j].state = 0;
            tiles[i][j].button->getLabel().getText().setFillColor(sf::Color::Black);

            //--- Normal continuation
            int randval = rand() % 4;
            if(randval == 0) {
                tiles[i][j].value = -1;
                // tiles[i][j].button->setMessage("*");
            }
        }
    }

    for(int i=0; i<gridSize.y; i++)
    {
        for(int j=0; j<gridSize.x; j++)
        {
            if(tiles[i][j].value != -1)
            {
                if(i>0 && tiles[i-1][j].value == -1) tiles[i][j].value++;
                if(j>0 && tiles[i][j-1].value == -1) tiles[i][j].value++;
                if(i+1<gridSize.y && tiles[i+1][j].value == -1) tiles[i][j].value++;
                if(j+1<gridSize.x && tiles[i][j+1].value == -1) tiles[i][j].value++;

                if(j+1<gridSize.x && i+1<gridSize.y && tiles[i+1][j+1].value == -1) tiles[i][j].value++;
                if(j>0 && i+1<gridSize.y && tiles[i+1][j-1].value == -1) tiles[i][j].value++;
                if(j<gridSize.x && i>0 && tiles[i-1][j+1].value == -1) tiles[i][j].value++;
                if(j>0 && i>0 && tiles[i-1][j-1].value == -1) tiles[i][j].value++;

                if(tiles[i][j].value != 0)
                {
                    tiles[i][j].button->getLabel().getText().setFillColor(valueColors[tiles[i][j].value-1]);
                }
            }
        }
    }
}

void generateMap(sf::Vector2f coords, std::vector<std::vector<Tile>>& tiles, sf::Vector2i gridSize)
{
    for(int seed = 0; seed <= MAX_SEED; seed++)
    {
        srand(seed);
        createMapValues(tiles, gridSize);

        if(tiles[coords.y][coords.x].value == 0) 
        {
            printf("generateMap(): created map with a seed: %i\n",seed);
            break;
        }
    }
}

int main()
{
//--- Variables
    const sf::Vector2u screenResolution = {1000u, 1000u};
    const sf::Vector2f menuSize = {600.f, 800.f};
    const sf::Vector2f buttonSize = {60.f, 60.f};
    const sf::Vector2f gap = {5.f,5.f};
    const sf::Vector2i gridSize = {9, 12};

    auto window = sf::RenderWindow(sf::VideoMode(screenResolution), "Minesweeper");
    window.setFramerateLimit(60);

    gui::DefaultMenu menu("default menu", {0,0}, menuSize, sf::Color(60,60,60), sf::Color(170, 100, 20), 20, &window);
    gui::Grid grid(buttonSize + gap, gridSize, 1);
    std::vector<std::vector<Tile>> tiles(gridSize.y);
    
//--- Setting up grid
    for(int i=0; i<gridSize.y; i++)
    {
        for(int j=0; j<gridSize.x; j++)
        {
            tiles[i].push_back(Tile());
            tiles[i][j].button = new gui::Button(buttonSize, sf::Color(170,170,170), sf::Color(0,0,0), &window, " ", 20);
            grid.setElement({j, i}, tiles[i][j].button);
        }
    }

    printf("[main.cpp] Menu's position: %f, %f\n", menu.getPosition().x, menu.getPosition().y);
    menu.setPosition({0,0});

    menu.addElement(&grid);

//--- Main cycle
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        //--- Button update
        for(int i=0; i<gridSize.y; i++)
        {
            for(int j=0; j<gridSize.x; j++)
            {
                if(tiles[i][j].button->isClicked(sf::Mouse::Button::Left) && tiles[i][j].state == 0)
                {
                    //--- Generating map first time with empty space
                    if(generated_map == false)
                    {
                        generateMap(sf::Vector2f(j,i), tiles, gridSize);
                        generated_map = true;
                    }

                    //--- If map was already generated
                    switch (tiles[i][j].state)
                    {
                    case 0:
                        if(tiles[i][j].value == 0)
                        {
                            showEmptyArea(tiles, {i,j}, gridSize, 0);
                        }
                        else if(tiles[i][j].value == -1) {}
                        else
                        {
                            showCell(tiles, {i,j});
                        }
                        break;
                    
                    default:
                        break;
                    }
                }

                if(tiles[i][j].button->isClicked(sf::Mouse::Button::Right) && tiles[i][j].state % 2 == 0)
                {
                    tiles[i][j].state = 2-tiles[i][j].state;
                    tiles[i][j].button->setIdleColor((tiles[i][j].state == 2 ? sf::Color::Red : sf::Color(170,170,170)));
                }
            }
        }

        menu.update(window.getView());

        window.clear();
        window.draw(menu);
        window.display();
    }
}

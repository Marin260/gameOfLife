#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Cell{
    private:
        sf::RectangleShape cell; // Graphic representation of a cell
        bool state; // cell state
    
    public:
        std::vector<std::vector<int>> neighbours;
        Cell(){
            cell.setSize(sf::Vector2f(25.f, 25.f));       //
            cell.setFillColor(sf::Color(255, 255, 255));  // Creating circle
            cell.setPosition(sf::Vector2f(0.f, 1.f));     //

            state = false; // Setting cell state to dead
        }
        Cell(bool cellState, sf::Vector2f cellPosition){
            cell.setSize(sf::Vector2f(20.f, 20.f));
            cell.setFillColor(sf::Color(255, 255, 255));
            cell.setPosition(cellPosition);

            state = cellState;
            if(state){cell.setFillColor(sf::Color(0, 0, 0));}
            else {cell.setFillColor(sf::Color(255, 255, 255));}
        }

        sf::RectangleShape getShape(){return cell;} // Required for drawing the cell
        void setColor(){cell.setFillColor(sf::Color(0, 0, 0));}
        void setState(bool cellState){
            state = cellState;
            if(state){cell.setFillColor(sf::Color(0, 0, 0));}
            else {cell.setFillColor(sf::Color(255, 255, 255));}
        }
};

int main()
{
    const int grid_size = 35;
    sf::RenderWindow window(sf::VideoMode(714, 714), "Game of life");
    Cell grid[grid_size][grid_size];

    sf::Vector2f pos(0.f, 0.f);
    for (int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            grid[i][j] = Cell(0, pos);
            pos.x += 21.f;
        }
        pos.x = 0.f;
        pos.y += 21.f;
    }

    for (int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            if (j != 0 && j != grid_size-1 && i != 0 && i != grid_size-1){
                for (int k = i-1; k < i+2; k++){
                    for (int l = j-1; l < j+2; l++){
                        if(k==i && l==j) continue;
                        grid[i][j].neighbours.push_back({k, l});
                    }
                }
            }
        } 
    }

    for (int i = 0; i < 8; i++){
        grid[grid[10][15].neighbours[i][0]][grid[10][15].neighbours[i][1]].setColor();
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(test.getShape());
        for (int i = 0; i < grid_size; i++)
            for(int j = 0; j < grid_size; j++)
                window.draw(grid[i][j].getShape());
        window.display();
    }

    return 0;
}
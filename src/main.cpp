#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Cell{
    private:
        sf::RectangleShape cell; // Graphic representation of a cell
        bool state; // cell state
        int neighbour;
    
    public:
        std::vector<std::vector<int>> neighbours;
        Cell(){
            cell.setSize(sf::Vector2f(25.f, 25.f));       //
            cell.setFillColor(sf::Color(255, 255, 255));  // Creating circle
            cell.setPosition(sf::Vector2f(0.f, 1.f));     //

            state = false; // Setting cell state to dead
            neighbour = 0;
        }
        Cell(bool cellState, sf::Vector2f cellPosition){
            cell.setSize(sf::Vector2f(20.f, 20.f));
            cell.setFillColor(sf::Color(255, 255, 255));
            cell.setPosition(cellPosition);

            state = cellState;
            neighbour = 0;
            if(state){cell.setFillColor(sf::Color(0, 0, 0));}
            else {cell.setFillColor(sf::Color(255, 255, 255));}
        }

        sf::RectangleShape getShape(){return cell;} // Required for drawing the cell
        void setColor(){cell.setFillColor(sf::Color(0, 0, 0));}
        void setState(bool cellState){
            // cell color depends on it's state
            state = cellState;
            if(state){cell.setFillColor(sf::Color(0, 0, 0));}
            else {cell.setFillColor(sf::Color(255, 255, 255));}
        }
        bool getState(){return state;}
        int getNg(){return neighbour;}
        void setNg(){neighbour += 1;}
        void setNg(int x){neighbour = x;}
        
};

int main()
{
    const int grid_size = 35;

    sf::RenderWindow window(sf::VideoMode(714, 714), "Game of life");
    window.setFramerateLimit(15);

    Cell grid[grid_size][grid_size];
    bool tmpGrid[grid_size][grid_size]={0};

    srand(time(NULL));

    sf::Vector2f pos(0.f, 0.f);
    for (int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            grid[i][j] = Cell(rand() % 2, pos);
            pos.x += 21.f;
        }
        pos.x = 0.f;
        pos.y += 21.f;
    }



    
    
        grid[15][14].setState(true);
        grid[15][15].setState(true);
        grid[15][16].setState(true);

        grid[1][2].setState(true);
        grid[2][3].setState(true);
        grid[3][3].setState(true);
        grid[3][2].setState(true);
        grid[3][1].setState(true);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                grid[i][j].setNg(0);
                tmpGrid[i][j]=false;
            }
        }
        


        for (int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                if (j != 0 && j != grid_size-1 && i != 0 && i != grid_size-1){
                    for (int k = i-1; k < i+2; k++){
                        for (int l = j-1; l < j+2; l++){
                            if (k==i && l==j) continue;
                            if (grid[k][l].getState()) grid[i][j].setNg();
                            //grid[i][j].neighbours.push_back({k, l});
                        }
                    }
                }
            }
        }
        // for (int i = 0; i < 8; i++){
        //     for(int j = 0; j < 2; j++){
        //         std::cout << grid[1][1].neighbours[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
    
        for (int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                if (grid[i][j].getState() && (grid[i][j].getNg() < 2 || grid[i][j].getNg() > 3)){
                    //std::cout << "stay\n";
                    tmpGrid[i][j]=false;
                }
                else if (!grid[i][j].getState() && grid[i][j].getNg() == 3){
                    //std::cout << "alive\n";
                    tmpGrid[i][j]=true;
                }
                else if (grid[i][j].getState() && (grid[i][j].getNg() == 2 || grid[i][j].getNg() == 3)) {
                    //std::cout << "eh\n";
                    tmpGrid[i][j]=true;
                }
            }
        }
        for (int i = 0; i < grid_size; i++){
            for(int j = 0; j < grid_size; j++){
                grid[i][j].setState(tmpGrid[i][j]);
            }
        }
        // for (int i = 0; i < grid_size; i++){
        //     for(int j = 0; j < grid_size; j++){
        //         std::cout << grid[i][j].getNg() << " ";
        //     }
        //     std::cout << std::endl;
        // }
        


        window.clear();
        //window.draw(test.getShape());
        for (int i = 0; i < grid_size; i++)
            for(int j = 0; j < grid_size; j++)
                window.draw(grid[i][j].getShape());
        window.display();
    }

    return 0;
}
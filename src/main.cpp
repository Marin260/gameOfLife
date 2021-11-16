#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Cell{
    private:
        sf::RectangleShape cell; // Graphic representation of a cell
        bool state; // cell state
        int neighbour;
    
    public:
        //std::vector<std::vector<int>> neighbours;
        Cell(){
            cell.setSize(sf::Vector2f(15.f, 15.f));       //
            cell.setFillColor(sf::Color(255, 255, 255));  // Creating circle
            cell.setPosition(sf::Vector2f(0.f, 1.f));     //

            state = false; // Setting cell state to dead
            neighbour = 0;
        }
        Cell(bool cellState, sf::Vector2f cellPosition){
            cell.setSize(sf::Vector2f(15.f, 15.f));
            cell.setFillColor(sf::Color(255, 255, 255));
            cell.setPosition(cellPosition);

            state = cellState;
            neighbour = 0;
            if(state){cell.setFillColor(sf::Color(0, 0, 0));}
            else {cell.setFillColor(sf::Color(255, 255, 255));}
        }

        sf::RectangleShape getShape(){return cell;} // Required for drawing the cell
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

const int grid_size = 60; // grid size 60X60 cells
void recursionForLoop(int sizeX, int sizeY, int constant, sf::RenderWindow &window, Cell grid[][grid_size], bool tmp[][grid_size], int funToDo);
void recursiveGridSetup(int sizeX, int sizeY, int constant,Cell grid[][grid_size], sf::Vector2f &pos);

int main()
{

    sf::RenderWindow window(sf::VideoMode(grid_size*16, grid_size*16), "Game of life"); // window size depends on grid size
    window.setFramerateLimit(15);

    Cell grid[grid_size][grid_size];
    bool tmpGrid[grid_size][grid_size]={0}; // Grid that contains next generation values

    srand(time(NULL));
    sf::Vector2f pos(0.f, 0.f);
    // for (int i = 0; i < grid_size; i++){
    //     for(int j = 0; j < grid_size; j++){
    //         grid[i][j] = Cell(rand() % 2, pos);
    //         pos.x += 16.f;
    //     }
    //     pos.x = 0.f;
    //     pos.y += 16.f;
    // }
    recursiveGridSetup(grid_size-1, grid_size-1, grid_size-1, grid, pos);


    // grid[15][14].setState(true);
    // grid[15][15].setState(true);
    // grid[15][16].setState(true);

    // grid[1][2].setState(true);
    // grid[2][3].setState(true);
    // grid[3][3].setState(true);
    // grid[3][2].setState(true);
    // grid[3][1].setState(true);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Reset alive neighbour with recursion
        recursionForLoop(grid_size-1, grid_size-1, grid_size-1, window, grid, tmpGrid, 4);

        // Find all the neighbours of every cell with a half recursion...
        recursionForLoop(grid_size-1, grid_size-1, grid_size-1, window, grid, tmpGrid, 5);

        // Add the coordinates of a cell neighbour to its vector
        // for (int i = 0; i < 8; i++){
        //     for(int j = 0; j < 2; j++){
        //         std::cout << grid[1][1].neighbours[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
    

        // Game of life logic with loops
        // for (int i = 0; i < grid_size; i++){
        //     for(int j = 0; j < grid_size; j++){
        //         if (grid[i][j].getState() && (grid[i][j].getNg() < 2 || grid[i][j].getNg() > 3))
        //             tmpGrid[i][j]=false;
        //         else if (!grid[i][j].getState() && grid[i][j].getNg() == 3)
        //             tmpGrid[i][j]=true;
        //         else if (grid[i][j].getState() && (grid[i][j].getNg() == 2 || grid[i][j].getNg() == 3)) 
        //             tmpGrid[i][j]=true;
        //     }
        // }

        // game of life logic with recursion
        recursionForLoop(grid_size-1, grid_size-1, grid_size-1, window, grid, tmpGrid, 3);


        // New cell state with loops
        // for (int i = 0; i < grid_size; i++){
        //     for(int j = 0; j < grid_size; j++){
        //         grid[i][j].setState(tmpGrid[i][j]);
        //     }
        // }

        // New cell state with recursion
        recursionForLoop(grid_size-1, grid_size-1, grid_size-1, window, grid, tmpGrid, 1);

        // for (int i = 0; i < grid_size; i++){
        //     for(int j = 0; j < grid_size; j++){
        //         std::cout << grid[i][j].getNg() << " ";
        //     }
        //     std::cout << std::endl;
        // }

        window.clear();

        // draw grid with loops
        // for (int i = 0; i < grid_size; i++)
        //     for(int j = 0; j < grid_size; j++)
        //         window.draw(grid[i][j].getShape());

        // draw grid with recursion
        recursionForLoop(grid_size-1, grid_size-1, grid_size-1, window, grid, tmpGrid, 2);

        window.display();
    }

    return 0;
}

void recursionForLoop(int sizeX, int sizeY, int constant, sf::RenderWindow &window, Cell grid[][grid_size], bool tmp[][grid_size], int funToDo){
    if (sizeX == 0 && sizeY < 0) return; // end loop when no more rows and columns
    else if(sizeY < 0) // if end of row restart in a new row
        recursionForLoop(sizeX-1, constant, constant, window, grid, tmp, funToDo);
    else {
        // else for every cell in the grid do something
        switch (funToDo){
            case 1:
                grid[sizeX][sizeY].setState(tmp[sizeX][sizeY]); // set a new cell state
                break;
            case 2:
                window.draw(grid[sizeX][sizeY].getShape()); // draw every cell in a grid
                break;
            case 3:
                // game of life logic
                if (grid[sizeX][sizeY].getState() && (grid[sizeX][sizeY].getNg() < 2 || grid[sizeX][sizeY].getNg() > 3))
                    tmp[sizeX][sizeY]=false;
                else if (!grid[sizeX][sizeY].getState() && grid[sizeX][sizeY].getNg() == 3)
                    tmp[sizeX][sizeY]=true;
                else if (grid[sizeX][sizeY].getState() && (grid[sizeX][sizeY].getNg() == 2 || grid[sizeX][sizeY].getNg() == 3)) 
                    tmp[sizeX][sizeY]=true;
                break;
            case 4:
                grid[sizeX][sizeY].setNg(0); // reset the number of neighbours of every cell after a new generation
                break;
            case 5:
                // find all the alive neighbours of every cell
                if (sizeY != 0 && sizeY != constant && sizeX != 0 && sizeX != constant){
                    // Yeaaa no recursion here...
                    for (int k = sizeX-1; k < sizeX+2; k++){
                        for (int l = sizeY-1; l < sizeY+2; l++){
                            if (k==sizeX && l==sizeY) continue;
                            if (grid[k][l].getState()) grid[sizeX][sizeY].setNg();
                            //grid[i][j].neighbours.push_back({k, l});
                        }
                    }
                }
                break;                
        }
        recursionForLoop(sizeX, sizeY-1, constant, window, grid, tmp, funToDo);
    }
}
void recursiveGridSetup(int sizeX, int sizeY, int constant,Cell grid[][grid_size], sf::Vector2f &pos){
    if (sizeX == 0 && sizeY < 0) return;  // end loop when no more rows and columns
    else if(sizeY < 0){ // if end of row restart in a new row
        pos.x = 0.f;
        pos.y += 16.f;
        recursiveGridSetup(sizeX-1, constant, constant, grid, pos);
    }
    else {
        // else for every cell in the grid do something
        grid[sizeX][sizeY] = Cell(rand() % 2, pos);
        pos.x += 16.f;
        recursiveGridSetup(sizeX, sizeY-1, constant, grid, pos);
    }
}
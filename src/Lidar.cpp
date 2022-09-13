#include "../include/Lidar.h"


Lidar::Lidar()
{}

Lidar::~Lidar(){}


void Lidar::MainLoop()
{
    //This will be the main spot to update obstacles around the lidar system

}

void Lidar::ResetGrid(int x, int y)
{   

    grid[y * grid_width + x].obstacle = RandomizeObstacle();
    grid[y * grid_width + x].visited = false;
    grid[y * grid_width + x].is_lidar = false;
    grid[y * grid_width + x].parent = nullptr;
    grid[y * grid_width + x].x_coord = x;
    grid[y * grid_width + x].y_coord = y;
}


bool Lidar::RandomizeObstacle()
{
    //std::srand(static_cast<unsigned int>(std::time(nullptr))); 

    int random_number = std::rand() % 100;

    std::cout << random_number << std::endl;

    if(random_number == 10)
        return true;

    return false;
}
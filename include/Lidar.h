#ifndef LIDAR_H
#define LIDAR_H

#include "Node.h"

//Standards Libs
#include <array>
#include <cstdlib>
#include <iostream>
#include <random>

class Lidar {

public:
Lidar();
~Lidar();

void MainLoop();

std::array<Node, 2048> grid;
void ResetGrid(int x, int y);

private:

std::uint8_t grid_width{64};
std::uint8_t grid_height{32};

//Randomize Obstacle Creation Until Data Input
bool RandomizeObstacle();

};

#endif
#ifndef LIDAR_H
#define LIDAR_H

#include "Node.h"
#include <array>

class Lidar {

public:
Lidar();
~Lidar();

void MainLoop();

//TODO:: Allow user to fine tune size of the grid
std::array<Node, 2048> grid;

private:


};

#endif
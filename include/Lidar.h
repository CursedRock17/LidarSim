#ifndef LIDAR_H
#define LIDAR_H

#include "Graphics.h"

class Lidar {

public:
Lidar();
~Lidar();

void MainLoop();

private:
//Need to draw stuff inside of the lidar
GraphicsClass g;

float lidarRadius = 100.0f;


};

#endif
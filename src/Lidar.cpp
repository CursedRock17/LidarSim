#include "../include/Lidar.h"

Lidar::Lidar()
{}

Lidar::~Lidar(){}


void Lidar::MainLoop()
{
    g.CreateLidar(lidarRadius);

    while(!g.graphics_should_stop)
    {
        g.Graphics_Loop();
        g.Check_Status();
    }
}
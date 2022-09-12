#include "../include/Lidar.h"

Lidar::Lidar()
{}

Lidar::~Lidar(){}


void Lidar::MainLoop()
{
    while(!g.graphics_should_stop)
    {
        g.Graphics_Loop();
        g.Check_Status();
    }
}
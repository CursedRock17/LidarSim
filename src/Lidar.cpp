#include "../include/Lidar.h"

void Lidar::Bob(){
    GraphicsClass g;

    while(!g.graphics_should_stop)
    {
        g.Graphics_Loop();
        g.Check_Status();
    }
}
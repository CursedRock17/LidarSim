#include <iostream>
#include "include/Graphics.h"

int main(int argc, char** argv){
    GraphicsClass gfx;

    while(!gfx.graphics_should_stop)
    {
        gfx.Check_Status();
        gfx.Graphics_Loop();
    }

    return 0;
}
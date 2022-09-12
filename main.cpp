#include <iostream>
#include "include/Graphics.h"

int main(int argc, char** argv){
    GraphicsClass gfx;

    while(!gfx.graphics_should_stop)
    {
        gfx.Graphics_Loop();
        gfx.Check_Status();
    }

    return 0;
}
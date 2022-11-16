#include <iostream>
#include "./include/Graphics_Headers/Graphics.h"


int main(int argc, char** argv){
    Graphics g;
    g.CreateShaders();
    g.RenderingLoop();
    return 0;
}
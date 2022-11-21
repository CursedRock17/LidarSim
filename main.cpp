#include <iostream>
#include "./include/Graphics_Headers/Graphics.h"
#include "./include/Space_Headers/Space.h"

int main(int argc, char** argv){
    Graphics g;
    Space spc;
    Gizmos giz;

    // Setup for Rendering Cycle //
    giz.CreateShaders("./src/Graphics/vertex.glsl", "./src/Graphics/fragment.glsl");
    giz.RenderTextures();
    // Run the cycle //
    g.RenderingLoop();

    return 0;
}

#include <iostream>
#include "./include/Graphics_Headers/Graphics.h"
#include "./include/Space_Headers/Space.h"

int main(int argc, char** argv){
    Graphics g;

    g.SimulationSetup();
    // Run the cycle //
    g.SimulationLoop();

    return 0;
}

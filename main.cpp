#include <iostream>
#include "include/Lidar.h"

int main(int argc, char** argv){
    std::cout << "Hello World" << std::endl;
    Lidar l;
    
    l.MainLoop();
    return 0;
}
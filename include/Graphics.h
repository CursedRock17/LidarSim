#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>

//Standard Libraries
#include <cmath>
#include <iostream>


class GraphicsClass {
public:
GraphicsClass();
~GraphicsClass();

//Running the Loop
bool graphics_should_stop{false};
void Check_Status();
void Graphics_Loop();

//Lidar Equipment
void CreateLidar(float radius);

private:

//All the SDL objects
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;

void GraphicsInit();
void GraphicsTerminate();

void Add_Delay();

int WINDOW_WIDTH = 960;
int WINDOW_HEIGHT = 480;

};

#endif
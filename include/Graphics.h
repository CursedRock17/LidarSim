#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>

//Our Libraries
#include "Node.h"
#include "Lidar.h"

//Standard Libraries
#include <cmath>
#include <iostream>
#include <array>


class GraphicsClass {
public:
GraphicsClass();
~GraphicsClass();

//Running the Loop
bool graphics_should_stop{false};
void Check_Status();
void Graphics_Loop();

private:

//All the SDL objects
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;

//Going to create a grid out of squares
SDL_Rect Pixel;
std::uint8_t pixel_size{15};

Lidar lidar_ref;

void GraphicsInit();
void GraphicsTerminate();

void Add_Delay();

//Grid Based Stuff
int CreateGrid();
void GraphicsUpdate();

int WINDOW_WIDTH = 960;
int WINDOW_HEIGHT = 480;

int grid_height{32};
int grid_width{64};


};
#endif
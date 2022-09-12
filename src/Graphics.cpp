#include "../include/Graphics.h"
#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>

GraphicsClass::GraphicsClass()
{
    GraphicsInit();
}

GraphicsClass::~GraphicsClass()
{
    GraphicsTerminate();
}

void GraphicsClass::Graphics_Loop()
{
    //Need to clear the colors and make sure we start by drawing on a black backgrfound

    //Check to make sure the window needs to stay up

    Add_Delay();
}
void GraphicsClass::Add_Delay()
{
    SDL_Delay(10);
}

void GraphicsClass::Check_Status()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            graphics_should_stop = true;
    }
}

void GraphicsClass::GraphicsInit()
{
SDL_Init(SDL_INIT_VIDEO);
window = SDL_CreateWindow("Lidar Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
renderer = SDL_CreateRenderer(window, -1, 0);

SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
SDL_RenderClear(renderer);
}

void GraphicsClass::GraphicsTerminate()
{

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


}

// --------- Lidar Graphics --------- //


// --------- Lidar Graphics --------- //



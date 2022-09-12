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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);

    //Go through the size of the graphics
    GraphicsUpdate();

    SDL_RenderPresent(renderer);

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

Pixel.h = pixel_size - 1;
Pixel.w = pixel_size - 1;

CreateGrid();

}

void GraphicsClass::GraphicsTerminate()
{

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


}

// --------- Lidar Graphics --------- //

/* When creating the map it'll become the shape of a grid
This grid will be fine tuned to fit all the data passed to it
*/

int GraphicsClass::CreateGrid()
{
        for(int x = 0; x < grid_width; x++){
            for(int y = 0; y < grid_height; y++){
            
            //Create a copy of each pixel and displace it by PIXEL_SIZE            
            Pixel.x = pixel_size * x;
            Pixel.y = pixel_size * y;

            //Set A Basic state for all of the grid
            lidar_ref.grid[y * grid_width + x].visited = false;
            lidar_ref.grid[y * grid_width + x].obstacle = false;
            lidar_ref.grid[y * grid_width + x].x_coord = x;
            lidar_ref.grid[y * grid_width + x].y_coord = y;
            lidar_ref.grid[y * grid_width + x].parent = nullptr;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        
            //Fill the pxiels will whatever color needs to be set for out path
            SDL_RenderDrawRect(renderer, &Pixel);
            SDL_RenderFillRect(renderer, &Pixel);
        }
    }

    //These have to be split because we need the data for pointers
    for(int x = 0; x < grid_width; ++x){
        for(int y = 0; y < grid_height; ++y){

            //We need to make sure each of these grid has filled out neighbors and that we don't have grid that dont exist
            if(y > 0)
                lidar_ref.grid[y * grid_width + x].neighbors.push_back(&lidar_ref.grid[(y - 1) * grid_width + (x)]);
            if(y < grid_height - 1)
                lidar_ref.grid[y * grid_width + x].neighbors.push_back(&lidar_ref.grid[(y + 1) * grid_width + (x)]);
            if(x > 0)
                lidar_ref.grid[y * grid_width + x].neighbors.push_back(&lidar_ref.grid[(y) * grid_width + (x - 1)]);
            if(x < grid_width -1)
                lidar_ref.grid[y * grid_width + x].neighbors.push_back(&lidar_ref.grid[(y) * grid_width + (x + 1)]);

        }
    }

    return -1;
}

void GraphicsClass::GraphicsUpdate()
{
    for(auto node : lidar_ref.grid){
            //We already have the coordinate data stored in the Node Class so we can just use that
            Pixel.x = pixel_size * node.x_coord;
            Pixel.y = pixel_size * node.y_coord;

            //Create a loop that checks through each thing to see if it's become an obstacle
            if(node.obstacle){
                //Make obstacles light blue
                SDL_SetRenderDrawColor(renderer, 8, 197, 255, 1);
            }

            //May need a way to check for local position TODO::

            else if(node.visited){
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);  
            }

            else {
                //Defualt Squares can be white
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
            }
            //Fill the pxiels will whatever color needs to be set for out path
            SDL_RenderDrawRect(renderer, &Pixel);
            SDL_RenderFillRect(renderer, &Pixel);

        }
}

// --------- Lidar Graphics --------- //



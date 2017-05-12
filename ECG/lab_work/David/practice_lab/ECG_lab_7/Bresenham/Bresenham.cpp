//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include <vector>
#include "vec3.h"
#include "clip.h"
#include <algorithm>

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//The window
SDL_Window *window = NULL;
//The window renderer
SDL_Renderer* renderer = NULL;
SDL_Event currentEvent;

bool quit = false;

int mouseX, mouseY;

typedef struct _line
{
	int startX;
	int startY;
	int endX;
	int endY;
} Line;

Line myLine;
Line myWindow;

std::vector<egc::vec3> clippingWindow;

int(*clipping_function)(std::vector<egc::vec3> clipWindow, egc::vec3& p1, egc::vec3& p2) = egc::lineClip_CyrusBeck;

bool initWindow()
{
    bool success = true;
    
    //Try to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else{
        //Try to create the window
        window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        
        if(window == NULL)
        {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
        }
    }
    
    return success;
}

void destroyWindow()
{
    //Destroy window
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
	renderer = NULL;
    //Quit SDL
    SDL_Quit();
}

void create_clipping_window()
{
	clippingWindow.clear();
	int minx = std::min(myWindow.startX, myWindow.endX);
	int miny = std::min(myWindow.startY, myWindow.endY);
	int maxx = std::max(myWindow.startX, myWindow.endX);
	int maxy = std::max(myWindow.startY, myWindow.endY);
	egc::vec3 v1 = egc::vec3(minx, miny, 0);
	egc::vec3 v2 = egc::vec3(minx, maxy, 0);
	egc::vec3 v3 = egc::vec3(maxx, maxy, 0);
	egc::vec3 v4 = egc::vec3(maxx, miny, 0);
	
	clippingWindow.push_back(v1);
	clippingWindow.push_back(v2);
	clippingWindow.push_back(v3);
	clippingWindow.push_back(v4);

}

void handleMouseEvents()
{
	//Mouse event -> pressed button
	if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (currentEvent.button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			myLine.startX = myLine.endX = mouseX;
			myLine.startY = myLine.endY = mouseY;
		}

		if (currentEvent.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			myWindow.startX = mouseX;
			myWindow.startY = mouseY;
		}
	}
		
	//Mouse event -> mouse movement
	if (currentEvent.type == SDL_MOUSEMOTION)
	{
		if (currentEvent.button.button & SDL_BUTTON_LMASK)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			myLine.endX = mouseX;
			myLine.endY = mouseY;
		}
		
		if (currentEvent.button.button & SDL_BUTTON_RMASK)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			myWindow.endX = mouseX;
			myWindow.endY = mouseY;
		}
	} 
}

void handleKeyboardEvents()
{
	//Keyboard event
	if (currentEvent.type == SDL_KEYDOWN)
	{
		switch (currentEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = true;
			break;

		case SDLK_1:
			std::cout << std::endl << "clipping function set to CyrusBeck" << std::endl;
			clipping_function = egc::lineClip_CyrusBeck;
			break;

		case SDLK_2:
			std::cout << std::endl << "clipping function set to CohenSutherland" << std::endl;
			clipping_function = egc::lineClip_CohenSutherland;
			break;

		default:		
			break;
		}
	}
}


int main(int argc, char * argv[]) {
    if(!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }

    while (!quit) {
        //Handle events on queue
		while (SDL_PollEvent(&currentEvent) != 0)
        {
            //User requests quit
            if(currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            
			handleMouseEvents();
			handleKeyboardEvents();
            
			//Clear screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			create_clipping_window();

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			int size = clippingWindow.size();
			for(int i = 0 ; i < size; i++) {
				egc::vec3 beg = clippingWindow[i];
				egc::vec3 end = clippingWindow[(i + 1) % size];
				SDL_RenderDrawLine(renderer, beg.x, beg.y, end.x, end.y);
			}
			egc::vec3 start = egc::vec3(myLine.startX, myLine.startY, 0);
			egc::vec3 end = egc::vec3(myLine.endX, myLine.endY, 0);

			std::cout << "before clipping: start: x: " << start.x << " y: " << start.y << " end: x: " << end.x << " y: " << end.y << std::endl;
			if (clipping_function(clippingWindow, start, end) == 0) {
				SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
			}
			
			std::cout << "after clipping: start: x: " << start.x << " y: " << start.y << " end: x: " << end.x << " y: " << end.y << std::endl;

			//Update screen
			SDL_RenderPresent(renderer);
        }
    }
    
    destroyWindow();
    return 0;
}

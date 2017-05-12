//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "transform.h"
#include "vec2.h"
#include "vec3.h"
#include "mat3.h"

using namespace egc;

SDL_Renderer *windowRenderer;
// define rectangle vertices
vec3 P1(100, 100, 1), P2(400, 100, 1);

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = {100, 100, 200, 200};
Uint32 rectagleColor;

bool quit = false;

int mouseX, mouseY;

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
            //Try to get the window surface
            windowSurface = SDL_GetWindowSurface(window);

            if(windowSurface == NULL)
            {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize surface color
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
                
                //Update the surface
                SDL_UpdateWindowSurface(window);
            }

			// Create a renderer for the current window
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if(windowRenderer == NULL)
            {
                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Set background color
				SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			
                //Apply background color
                SDL_RenderClear(windowRenderer);
            }

        }
    }
    
    return success;
}

void destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    
    //Quit SDL
    SDL_Quit();
}

void drawRect(vec3 a1, vec3 a2, vec3 a3, vec3 a4) {
	SDL_RenderDrawLine(windowRenderer, a1.x, a1.y, a2.x, a2.y);
	SDL_RenderDrawLine(windowRenderer,a2.x, a2.y, a3.x, a3.y);
	SDL_RenderDrawLine(windowRenderer, a3.x, a3.y, a4.x,a4.y);
	SDL_RenderDrawLine(windowRenderer, a4.x, a4.y, a1.x, a1.y);
}

vec3 rotateFPoint(const vec3 point, const vec2 middle) {
	mat3 trans,transI,rot;
	vec3 aux;
	for (int i = 0; i < 9; i++) {
		trans.matrixData[i] = translate(middle).matrixData[i];
	}
	transI = translate(-1 * middle.x, -1 * middle.y);
	aux = trans*point;
	rot = rotate(10);
	aux = rot*aux;
	aux = transI*aux;
	return aux;

}

vec3 rotateBPoint(const vec3 point, const vec2 middle) {
	mat3 trans, transI, rot;
	vec3 aux;
	for (int i = 0; i < 9; i++) {
		trans.matrixData[i] = translate(middle).matrixData[i];
	}
	transI = translate(-1 * middle.x, -1 * middle.y);
	aux = trans*point;
	rot = rotate(-10);
	aux = rot*aux;
	aux = transI*aux;
	return aux;

}

int main(int argc, char * argv[]) {
    if(!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }
    
    rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
    
    while (!quit) {
        //Handle events on queue
        if(SDL_WaitEvent(&currentEvent) != 0)
        {
            //User requests quit
            if(currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            
            //Mouse event -> pressed button
            if(currentEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
            
            //Mouse event -> mouse movement
            if(currentEvent.type == SDL_MOUSEMOTION)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
            //Draw initial rectangle
			vec3 a1(100, 100, 1), a2(200, 100, 1), a3(200, 200, 1), a4(100, 200, 1);
			vec2 middle(a1.y + (a4.y - a1.y) / 2, a1.x + (a2.x - a1.x) / 2);

			drawRect(a1, a2, a3, a4);

			SDL_UpdateWindowSurface(window);

			SDL_RenderPresent(windowRenderer);
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {
                    case SDLK_UP:
                        rectagleColor = SDL_MapRGB(windowSurface->format, 0, 255, 0);
                        break;
                        
                    case SDLK_LEFT:
						drawRect(rotateFPoint(a1,middle),rotateFPoint(a2,middle), rotateFPoint(a3,middle), rotateFPoint(a4,middle));
						SDL_RenderPresent(windowRenderer);
						break;

					case SDLK_RIGHT:
						drawRect(rotateBPoint(a1, middle), rotateBPoint(a2, middle), rotateBPoint(a3, middle), rotateBPoint(a4, middle));
						SDL_RenderPresent(windowRenderer);
						break;

                        
                    default:
                        rectagleColor = SDL_MapRGB(windowSurface->format, 255, 255, 0);
                        break;
                }
            }
            
			// DISPLAY METHOD USED IN LABORATORY 1
            //SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
            //SDL_UpdateWindowSurface(window);
			// end

			SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			SDL_RenderClear(windowRenderer);

			SDL_SetRenderDrawColor(windowRenderer, 0, 0,255, 255);
			//SDL_RenderDrawLine(windowRenderer, P1.x, P1.y, P2.x, P2.y);
			
			SDL_RenderPresent(windowRenderer);
			

        }
    }
    
    destroyWindow();
    return 0;
}

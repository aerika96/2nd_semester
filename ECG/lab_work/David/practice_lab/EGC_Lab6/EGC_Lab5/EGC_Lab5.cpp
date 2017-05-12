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

int rotation_angle = 0;
float scaling_factor = 1;

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

void draw_rectangle(vec3 p1, vec3 p2, vec3 p3, vec3 p4)
{
	SDL_RenderDrawLine(windowRenderer, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderDrawLine(windowRenderer, p2.x, p2.y, p3.x, p3.y);
	SDL_RenderDrawLine(windowRenderer, p3.x, p3.y, p4.x, p4.y);
	SDL_RenderDrawLine(windowRenderer, p4.x, p4.y, p1.x, p1.y);
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
            
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {
					case SDLK_RIGHT:
						rotation_angle += 10;
						break;
					case SDLK_LEFT:
						rotation_angle -= 10;
						break;
                    case SDLK_UP:
						scaling_factor *= 1.1f;
                        break;
                    case SDLK_DOWN:
						scaling_factor *= 1/1.1f;
                        break;
                        
                    case SDLK_r:
                        rectagleColor = SDL_MapRGB(windowSurface->format, 255, 0, 0);
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

			SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);

			vec3 p1 = vec3(100, 100, 1);
			vec3 p2 = vec3(100, 400, 1);
			vec3 p3 = vec3(400, 400, 1);
			vec3 p4 = vec3(400, 100, 1);

			vec2 center = vec2((p1.x + p3.x) / 2, (p1.y + p3.y) / 2);

			mat3 back_from_center = translate(center);
			mat3 rotate_mat = rotate(rotation_angle);
			mat3 to_origin = translate(-center);

			mat3 rotate_around_center = back_from_center * rotate_mat * to_origin;
			mat3 scale_mat = translate(p1.x, p1.y) * scale(scaling_factor, scaling_factor) * translate(-p1.x, -p1.y);

			p1 = rotate_around_center*p1;
			p2 = rotate_around_center*p2;
			p3 = rotate_around_center*p3;
			p4 = rotate_around_center*p4;

			p1 = scale_mat*p1;
			p2 = scale_mat*p2;
			p3 = scale_mat*p3;
			p4 = scale_mat*p4;

			draw_rectangle(p1, p2, p3, p4);
			
			SDL_RenderPresent(windowRenderer);
        }
    }
    
    destroyWindow();
    return 0;
}

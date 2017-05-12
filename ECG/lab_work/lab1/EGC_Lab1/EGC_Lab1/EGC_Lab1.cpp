
//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = {100, 100, 200, 200};
Uint32 rectagleColor;

Uint8 redC=255;
Uint8 blueC = 255;
Uint8 greenC = 255;
char selected;

int coordX, coordY, width, height;


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

int main(int argc, char * argv[]) {
    if(!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }
    
    rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);
	coordX = 100;
	coordY = 100;
	width = 200;
	height = 200;

	
	SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);

	SDL_UpdateWindowSurface(window);

    
    while (!quit) {
        //Handle events on queue
        if(SDL_WaitEvent(&currentEvent) != 0)
        {
            //User requests quit
            if(currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }

			SDL_Rect rectCoord = { coordX,coordY,width,height };
			SDL_FillRect(windowSurface, &rectCoord, rectagleColor);
			SDL_UpdateWindowSurface(window);

            
            //Mouse event -> pressed button
            if(currentEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)

                {
					coordX = 0;
					coordY = 0;
					width = 0;
					height = 0;
					SDL_GetMouseState(&mouseX, &mouseY);

					coordX = mouseX;
					coordY = mouseY;
                }
            }
            
            //Mouse event -> mouse movement
            if(currentEvent.type == SDL_MOUSEMOTION)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
					
					width = 0;
					height = 0;
					
					SDL_GetMouseState(&mouseX,&mouseY);
					SDL_Rect rectCoord = { coordX,coordY,width,height };
					SDL_FillRect(windowSurface, &rectCoord, rectagleColor);
					SDL_UpdateWindowSurface(window);
					width = mouseX - coordX;
					height = mouseY - coordY;
                }
                
            }

			
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {
                    case SDLK_UP:
						if (selected == 'r' && redC < 255) redC++;
						else if (selected =='b' && blueC < 255) blueC++;
						else if (selected == 'g' && greenC < 255) greenC++;
						rectagleColor = SDL_MapRGB(windowSurface->format, redC,greenC,blueC);
						break;
					case SDLK_DOWN:
						if (selected == 'r' && redC >0 ) redC--;
						else if (selected == 'b' && blueC >0) blueC--;
						else if (selected == 'g' && greenC >0) greenC--;
						rectagleColor = SDL_MapRGB(windowSurface->format, redC, greenC, blueC);
						break;
                    case SDLK_r:
						selected = 'r';
                        break;
					case SDLK_g:
						selected = 'g';
						break;
					case SDLK_b:
						selected = 'b';
						break;
                    default:
                        rectagleColor = SDL_MapRGB(windowSurface->format, 255, 255, 0);
                        break;
                }
            }
			
			if (currentEvent.type == SDL_MOUSEBUTTONUP) {
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_Rect rectCoord = { coordX,coordY,width,height };
					SDL_FillRect(windowSurface, &rectCoord, rectagleColor);

					SDL_UpdateWindowSurface(window);

				}
			}
			
			
			SDL_UpdateWindowSurface(window);
            
            
        }
    }
    
    destroyWindow();
    return 0;
}

#include "Universe/universe.h"
#include "Universe/universeManager.h"
#include "Event/event.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
#include "../sdl/include/SDL2/SDL.h"


//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void Render(){
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_Rect screen;
	screen.x = 0;
	screen.y = 0;
	screen.w = SCREEN_WIDTH;
	screen.h = SCREEN_HEIGHT;
	SDL_RenderFillRect(renderer, &screen);
	SDL_RenderPresent(renderer);
}

int main() {
	Universe universe = Universe(1, 1, 1000, 1000);

	

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
	SDL_RenderClear( renderer );
	
	bool loop = true;
 
	while (loop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;
		}
		Render();
	}

	return 0;
}

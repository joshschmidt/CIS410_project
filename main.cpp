#include "Universe/universe.h"
#include "Galaxy/galaxyManager.h"
#include "Event/event.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <iostream>
#include "../sdl/include/SDL2/SDL.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int main() {
<<<<<<< HEAD
	Galaxy g = Galaxy(1,1,1);
	GalaxyManager gm = GalaxyManager(&g);
	Event e = Event(1,1,1,1);
	gm.addEvent(e);
	gm.nextEvent().printEvent();
	Universe universe = Universe(1, 1, 1000, 1000);

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
	SDL_RenderClear( gRenderer );


	return 0;
=======
	
>>>>>>> b9fe310cfd256fa9ad23b4a828e99c92ef48d652
}

#include "universeManager.h"    
#include <stdio.h>  
#include <stdlib.h>     
#include <time.h> 
#include "../../sdl/include/SDL2/SDL.h"

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

     
     
UniverseManager::UniverseManager(Universe * u) {
	universe = u;
        int length = universe->getLength();
        int width = universe->getWidth();
        for(int i = 0; i < length; i++) {
        	for(int j = 0; j < width; j++) {
	                managers.push_back(GalaxyManager(u->getGalaxy(i,j), universe));                
            	}
     
    	}
        Init();
    }
     
void UniverseManager::advanceSim() {
     
    //here is where the thread delegation goes to the individual galaxy managers
 
     
}

void UniverseManager::Render(){
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	SDL_Rect screen;
	screen.x = 0;
	screen.y = 0;
	screen.w = SCREEN_WIDTH;
	screen.h = SCREEN_HEIGHT;
	
	SDL_RenderFillRect(renderer, &screen);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 );
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			SDL_Rect galaxyIcon;
			galaxyIcon.x = (i * 50) + 50;
			galaxyIcon.y = (j * 50) + 50;
			galaxyIcon.w = 10;
			galaxyIcon.h = 10;
			
			SDL_RenderFillRect(renderer, &galaxyIcon);
		}
	}
	
	SDL_RenderPresent(renderer);
		
}


void UniverseManager::Init(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,  SDL_WINDOW_FULLSCREEN_DESKTOP );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
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
			if (event.type == SDL_KEYDOWN)
				loop = false;
		}
		Render();
	}
}


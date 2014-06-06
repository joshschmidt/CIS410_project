#include "universeManager.h"    
#include <stdio.h>  
#include <stdlib.h>     
#include <time.h> 
#include "../../sdl/include/SDL2/SDL.h"
#include "../../sdl/include/SDL2/SDL_ttf.h"
#include <math.h> 
#include <sstream>
#include <string> 
#include<unistd.h>
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

     
     
UniverseManager::UniverseManager(Universe * u) {
	universe = u;
    int length = universe->getLength();
    int width = universe->getWidth();
	managers = new std::vector<GalaxyManager*>;
    for(int i = 0; i < length; i++) {
    	for(int j = 0; j < width; j++) {
                managers->push_back(new GalaxyManager(u->getGalaxy(i,j), universe));                
        	}
 
	}

	cilk_for(int i = 0; i < managers->size(); i++) {
		//printf("%d", i);
		managers->at(i)->init();

	}
	
	InitSDL();
}
     
void UniverseManager::runSim() {
	
	int runLength = 10;
	int simTime = 0;

	while(simTime < 10) {

		for(int i = 0; i < managers->size(); i++) {
			managers->at(i)->advanceSim(100);	
		}

		simTime++;

	}
     
}

void UniverseManager::printUniverse() {
	universe->printUniverse();
}

void UniverseManager::Render(){

	
		
}


void UniverseManager::InitSDL(){
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The window renderer
	SDL_Renderer* renderer = NULL;
	if( SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		exit(2);
	}
	
	window = SDL_CreateWindow("UNIVERSE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,  0 );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		exit(2);
	}


	if(TTF_Init() == -1) {
	    printf("TTF_Init: %s\n", TTF_GetError());
	    exit(2);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderClear( renderer );	
	bool loop = true;

 	TTF_Font* Sans = NULL;
	Sans = TTF_OpenFont("font.TTF", 24);
	SDL_Color White = {255, 255, 255};  
	if(!Sans) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	    // handle error
	}
	while (loop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT){
				loop = false;
				exit(0);
				SDL_DestroyRenderer(renderer);
			  	SDL_DestroyWindow(window);
			  	SDL_Quit();

				break;
            }
			if (event.type == SDL_KEYDOWN){
				loop = false;
				exit(0);
				SDL_DestroyRenderer(renderer);
			  	SDL_DestroyWindow(window);
			  	SDL_Quit();
				break;
            }
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
		SDL_Rect screen;
		screen.x = 0;
		screen.y = 0;
		screen.w = SCREEN_WIDTH;
		screen.h = SCREEN_HEIGHT;
 		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &screen);
		double floodPercent = ((double) rand() / (RAND_MAX));
	    double civilianPercent = ((double) rand() / (RAND_MAX));
	    double militaryPercent = ((double) rand() / (RAND_MAX));
	    int barSize = 100; //100 pixels
		

		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				//Galaxy * g = universe->getGalaxy(i, j);
				
				SDL_Rect labelBounds;
				labelBounds.x = (i * 150) + 25;
				labelBounds.y = (j * 150) + 25;
				labelBounds.w = 100;
				labelBounds.h = 25;
				SDL_Surface* surfaceLabel = NULL;
				std::stringstream sstm;
				sstm << "Galaxy ("  << i << ", " << j << ")";

				std::string galaxyLabel = sstm.str();

				surfaceLabel = TTF_RenderText_Solid(Sans, galaxyLabel.c_str() , White);

				SDL_Texture* label = SDL_CreateTextureFromSurface(renderer, surfaceLabel); //now you can convert it into a texture
				SDL_RenderCopy(renderer, label, NULL, &labelBounds);
				SDL_Rect floodBar;
				floodBar.x = (i * 150) + 50;
				floodBar.y = (j * 150) + 50;
				floodBar.w = (int) 100 * floodPercent;
				floodBar.h = 25;
				SDL_SetRenderDrawColor(renderer, 140, 204, 4, 255);
				SDL_RenderFillRect(renderer, &floodBar);

	            SDL_Rect civilianBar;
	            civilianBar.x = (i * 150) + 50 + floodBar.w;
	            civilianBar.y = (j * 150) + 50;
	            civilianBar.w = (int) 100 * civilianPercent;
	            civilianBar.h = 25;
	            SDL_SetRenderDrawColor(renderer, 3, 62, 178, 255);
	            SDL_RenderFillRect(renderer, &civilianBar);

	            SDL_Rect militaryBar;
	            militaryBar.x = (i * 150) + 50 + floodBar.w + civilianBar.w;
	            militaryBar.y = (j * 150) + 50;
	            militaryBar.w = (int) 100 * militaryPercent;
	            militaryBar.h = 25;
	            SDL_SetRenderDrawColor(renderer, 255, 62, 15, 255);
	            SDL_RenderFillRect(renderer, &militaryBar);

			}
		}
		SDL_RenderPresent(renderer);
	}
	
}


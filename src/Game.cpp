//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>

#include "graphics/Texture.h"

#include "ai/Player.h"
#include "ai/Zombie.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
 void close();

//SDL_Surface* loadImg(std::string path);

//The window we'll be rendering to
SDL_Window* window = NULL;
	
Player player;
Zombie zombie;

std::vector<Zombie> zombies;

SDL_Renderer* renderer;


bool init() {
	puts("hi");
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		//Create window
		window = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			player.init(32, 32, renderer);
			//zombie.init(32, 32, renderer);
			for (Zombie &z : zombies) {
				z.init(32, 32, renderer);
			}

			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				//Initialize renderer color
				//SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true; 
	player.texture.loadFromFile("assets/old_assets/player.png");
	//zombie.texture.loadFromFile("assets/old_assets/zombie.png");
	for (Zombie &z : zombies) {
		z.texture.loadFromFile("assets/old_assets/zombie.png");
	}
	return success;
}

void close() {
	player.texture.free();
	zombie.texture.free();
	SDL_DestroyWindow( window );
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}

int main( int argc, char* args[] ) {
	player.x = 100;
	player.y = 100;
	zombies.emplace_back();
	//Start up SDL and create window
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	}
	else {
		//Load media
		if(!loadMedia()) {
			printf( "Failed to load media!\n" );
		}
		else
		{			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while(!quit) {
				//Handle events on queue
				while( SDL_PollEvent(&e) != 0 ) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					} else if (e.type == SDL_KEYDOWN) {
						if (e.key.keysym.sym == SDLK_UP){
							if (!(player.y < 0)){
								player.y-=3;
							}
						}
						else if (e.key.keysym.sym == SDLK_DOWN){
							if (!(player.y > 448)) {
							player.y+=3;
							}
						}
						else if (e.key.keysym.sym == SDLK_LEFT){
							if (!(player.x < 0)) {
								player.x-=3;
							}
						}
						else if (e.key.keysym.sym == SDLK_RIGHT){
							if (!(player.x > 608)) {
								player.x+=3;
							}
						}
					}
				}

				//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

				SDL_SetRenderDrawColor(renderer, 0x00, 0xCC, 0x66, 0xFF);
				SDL_RenderClear(renderer);

				if (SDL_GetTicks() % 80 == 0) {
					//zombie.move(player); //player dissapears when zombie.move is called
					for (Zombie &z : zombies) {
						z.move(player);
					}
					//puts("moved!");
				}
				//zombie.render();
				player.render();
				for (Zombie &z : zombies) {
					z.render();
				}
				

				//Update screen
				SDL_RenderPresent(renderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
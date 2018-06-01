#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Texture.h"

    //Initializes variables
Texture::Texture() {
    this->texture = NULL;
    this->width = 0;
    this->height = 0;
}

//Deallocates memory
Texture::~Texture() {
    free();
}

//Loads image at specified path
bool Texture::loadFromFile( std::string path ) {
    //Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			// this->width = loadedSurface->w*20;
			// this->height = loadedSurface->h*15;
		}

		//Get rid of old loaded surface
        if (this->width == 0 || this->height == 0) {
            puts("w/h not set! this will not work soon!!");
            this->width = loadedSurface->w*20;
			this->height = loadedSurface->h*15;
        }
        SDL_FreeSurface( loadedSurface );
	}

	//Return success
	this->texture = newTexture;
	return this->texture != NULL;
}

//Deallocates texture
void Texture::free() {
    if( this->texture != NULL ){
        SDL_DestroyTexture( this->texture );
        this->texture = NULL;
        width = 0;
        height = 0;
    }
}

//Set color modulation
void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
    SDL_SetTextureColorMod( this->texture, red, green, blue );
}

//Renders texture at given point
void Texture::render( int x, int y, SDL_Rect* clip ) {
    //Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, this->width, this->height };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( this->renderer, this->texture, clip, &renderQuad );
}

//Gets image dimensions
int Texture::getWidth() {
    return this->width;
}
int Texture::getHeight() {
    return this->height;
}
void Texture::setWH(int width, int height) {
    this->width = width;
    this->height = height;
}
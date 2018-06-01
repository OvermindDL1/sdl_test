#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Texture {
    public:
        SDL_Renderer* renderer;
        //Initializes variables
        Texture();

        //Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool loadFromFile( std::string path);

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL );

        //Gets image dimensions
        int getWidth();
        int getHeight();

        void setWH(int width, int height);

    //private:
        //The actual hardware texture
        SDL_Texture* texture;

        //Image dimensions
        int width;
        int height;
};
#endif
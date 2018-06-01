#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "../graphics/Texture.h"

class Player {
    public:
    Player(const Player&) = delete;
    Player();
    ~Player();
    int x;
    int y;
    int health;
    int maxHealth;
    Texture texture;
    
    void render();
    void init(int width, int height, SDL_Renderer* renderer);
};
#endif
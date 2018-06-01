#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Player.h"
#include "../graphics/Texture.h"

class Zombie {
    public:
    Zombie(const Zombie&) = delete;
    Zombie();
    ~Zombie();
    int x;
    int y;
    Texture texture;

    void move(Player& player);
    void render();
    void init(int width, int height, SDL_Renderer* renderer);
};
#endif
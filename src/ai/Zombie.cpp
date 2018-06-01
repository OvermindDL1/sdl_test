#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <cmath>
#include <string>

#include "Zombie.h"
#include "Player.h"


void Zombie::move(Player& player) {
    if(this->x > player.x){
        this->x-=1;
    }
    if(this->x < player.x){
        this->x+=1;
    }
    if(this->y > player.y){
        this->y-=1;
    }
    if(this->y < player.y){
        this->y+=1;
    }
}

void Zombie::render() {
    this->texture.render(this->x, this->y);
}

Zombie::Zombie(){
}

void Zombie::init(int width, int height, SDL_Renderer* renderer) {
    this->texture.setWH(width, height);
    this->texture.renderer = renderer;
}

Zombie::~Zombie(){
    this->texture.free();
}
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <string>
#include <cmath>

#include "Player.h"
#include "../graphics/Texture.h"

void Player::render() {
    //printf("%d, %d \n", this->x, this->y);
    this->texture.render(this->x, this->y);
}

Player::Player() {

}

void Player::init(int width, int height, SDL_Renderer* renderer) {
    this->texture.setWH(width, height);
    this->texture.renderer = renderer;
}
Player::~Player(){
    this->texture.free();
}

#pragma once
#include "renderer.h"
#include <SDL2/SDL_render.h>


typedef struct DrawingContext {
    Renderer * renderer;
    SDL_Texture * cactus_texture;
    SDL_Texture * player_texture;
    SDL_Texture * booster_texture;
    SDL_Texture * bullet_texture;
    SDL_Texture * monster_texture;
    SDL_Texture * monster_bullet_texture;
    SDL_Texture * coin_texture;

    SDL_Texture * explosion_texture;

    SDL_Texture * bg_texture;
    float bg_scroll_y;
    
    SDL_Texture * hud_texture;
    // only used for the hud
    float dt;
    
} DrawingContext;

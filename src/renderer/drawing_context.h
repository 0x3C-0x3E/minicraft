#pragma once
#include "renderer.h"
#include <SDL2/SDL_render.h>


typedef struct DrawingContext {
    Renderer * renderer;
    SDL_Texture * cactus_texture;
    SDL_Texture * player_texture;
    
    float dt;
} DrawingContext;

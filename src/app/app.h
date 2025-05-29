#pragma once
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "../constants.h"

#include "../renderer/renderer.h"
#include "../entity_pool/entity_pool.h"

typedef struct App {
    Renderer renderer;

    SDL_Texture * cactus_spritesheet;

    EntityPool entity_pool;

    bool running;

} App;

int app_init(App* app);

void app_quit(App* app);

void app_run(App * app);

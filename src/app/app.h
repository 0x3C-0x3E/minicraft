#pragma once
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "../constants.h"

#include "../renderer/renderer.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/entity_pool.h"

#include "../spawner/spawner_monster.h"

typedef struct App {
    Renderer renderer;
    DrawingContext drawing_context;

    float accumilator;
    float current_time;
    float global_time;
    float dt;

    GameState game_state;

    EntityPool entity_pool;

    SpawnerMonster spawner_monster;

    bool running;

} App;

int app_init_sdl(App * app);

int app_init(App* app);

void app_quit(App* app);

void app_run(App * app);

float app_hire_time_in_seconds();

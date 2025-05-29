#include "app.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int app_init(App* app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL!\n");
        return 1;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Could not init SDL_img!\n");
        return 1;
    }

    if (renderer_init(&app->renderer) == 1) {
        return 1;
    }

    app->cactus_spritesheet = renderer_load_texture(&app->renderer, "res/cactus.png");
    
    app->entity_pool.entity_count = 0;
    
    entity_pool_add_entity(&app->entity_pool, Type_Entity, 40, 0, (SDL_Rect) {0, 0, 16, 16}, app->cactus_spritesheet);

    
    return 0;
}

void app_quit(App* app) {
    SDL_DestroyRenderer(app->renderer.sdl_renderer);
    SDL_DestroyWindow(app->renderer.sdl_window);
}

void app_run(App * app) {
    while (app->running) {

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                app_quit(app);
                entity_pool_clear(&app->entity_pool);
                SDL_Quit();
                app->running = false;
                return;
            }
        }

        for (unsigned int i = 0; i < app->entity_pool.entity_count; i++) {
            Entity * e = (Entity*)app->entity_pool.entities[i];
            entity_update(e);
        }

        renderer_clear(&app->renderer);
        for (unsigned int i = 0; i < app->entity_pool.entity_count; i++) {
            Entity * e = (Entity*)app->entity_pool.entities[i];
            entity_draw(e, &app->renderer);
        }

        renderer_present(&app->renderer);

        SDL_Delay(16);
    }
}


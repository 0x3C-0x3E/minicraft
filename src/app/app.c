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
    
    Cactus * c = (Cactus *) entity_pool_add_entity(&app->entity_pool, Type_Cactus);
    *c = (Cactus) {
        .entity = {
            .x = 40,
            .y = 0,
            .img_rect = (SDL_Rect) {0, 0, 16, 16},
            .texture = app->cactus_spritesheet,
        },
        .has_stings = true,
    };
    
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
        
        //update
        entity_pool_update(&app->entity_pool);
        

        //render
        renderer_clear(&app->renderer);
        
        entity_pool_draw(&app->entity_pool, &app->renderer);

        renderer_present(&app->renderer);

        SDL_Delay(16);
    }
}


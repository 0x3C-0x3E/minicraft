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

    app->accumilator = 0.0f;
    app->current_time = app_hire_time_in_seconds();
    app->global_time = 0.0f;

    app->drawing_context = (DrawingContext) {
        .renderer = &app->renderer,
        .cactus_texture = renderer_load_texture(&app->renderer, "res/cactus.png"),
        .player_texture = renderer_load_texture(&app->renderer, "res/player.png"),
        .dt = 0.0f,
    };

    app->entity_pool = (EntityPool) {
        .entity_count = 0,
    };

    Player * p = (Player * ) entity_pool_add_entity(&app->entity_pool, Type_Player);
    *p = (Player) {
        .entity = {
            .x = DISPLAY_WIDTH / 2,
            .y = DISPLAY_HEIGHT - 50,
            .img_rect = (SDL_Rect) {16, 0, 16, 16},
            .texture = app->drawing_context.player_texture,
        },
    };
    
    return 0;
}

void app_quit(App* app) {
    SDL_DestroyRenderer(app->renderer.sdl_renderer);
    SDL_DestroyWindow(app->renderer.sdl_window);
}

void app_run(App * app) {
    while (app->running) {

        int start_ticks = SDL_GetTicks();
        float new_time = app_hire_time_in_seconds();
        float frame_time = new_time - app->current_time;

        app->dt = frame_time;
        app->drawing_context.dt = frame_time;

        app->current_time = new_time;
        app->accumilator += frame_time; 

        app->global_time += 1.0f;

        while (app->accumilator >= TIME_STEP) {
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

            app->accumilator -= TIME_STEP;
        }

               
        entity_pool_update(&app->entity_pool, app->drawing_context.dt);
        

        renderer_clear(&app->renderer);
        
        entity_pool_draw(&app->entity_pool, &app->drawing_context);

        renderer_present(&app->renderer);
        
        int frame_ticks = SDL_GetTicks() - start_ticks;

        if (frame_ticks < 1000/REFRESH_RATE) {
            SDL_Delay(1000 / REFRESH_RATE - frame_ticks);
        }
    }
}

float app_hire_time_in_seconds() {
    float t = SDL_GetTicks();
    t *= 0.001f;

    return t;
}

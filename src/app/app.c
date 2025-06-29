#include "app.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../constants.h"


int app_init_sdl(App * app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL!\n");
        return 1;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Could not init SDL_img!\n");
        return 1;
    }

    return 0;
}


int app_init(App* app) {

    if (app_init_sdl(app) == 1) {
        return 1;
    }

    if (renderer_init(&app->renderer) == 1) {
        return 1;
    }

    app->running = true;

    app->accumilator = 0.0f;
    app->current_time = app_hire_time_in_seconds();
    app->global_time = 0.0f;

    app->drawing_context = (DrawingContext) {
        .renderer = &app->renderer,
        .cactus_texture  = renderer_load_texture(&app->renderer, "res/cactus.png"),
        .player_texture  = renderer_load_texture(&app->renderer, "res/player.png"),
        .booster_texture = renderer_load_texture(&app->renderer, "res/booster.png"),
        .bullet_texture  = renderer_load_texture(&app->renderer, "res/bullet.png"),
        .monster_texture = renderer_load_texture(&app->renderer, "res/monster.png"),
        .monster_bullet_texture = renderer_load_texture(&app->renderer, "res/monster_bullet.png"),
        .explosion_texture = renderer_load_texture(&app->renderer, "res/explosion.png"),
        .bg_texture = renderer_load_texture(&app->renderer, "res/bg.png"),
        .bg_scroll_y = 0.0f,
        .hud_texture = renderer_load_texture(&app->renderer, "res/hud.png"),
        .coin_texture = renderer_load_texture(&app->renderer, "res/coin.png"),

    };

    app->entity_pool = (EntityPool) {
        .entity_count = 0,
    };
    
    // scuffed but should work
    // or does it??
    memset(&app->entity_pool.entity_count, 0, sizeof(int));

    hud_init(&app->hud);

    app->game_state = (GameState) {
        .entity_pool = &app->entity_pool,
        .hud = &app->hud,
        .dt = app->dt,
        .drawing_context = &app->drawing_context,
    };

    Player * p = (Player * ) entity_pool_add_entity(&app->entity_pool, Type_Player);
    *p = (Player) {
        .entity = {
            .x = (float) DISPLAY_WIDTH / 2 - 8,
            .y = (float) DISPLAY_HEIGHT - 50,
            .img_rect = (SDL_Rect) {16, 0, 16, 16},
            .texture = app->drawing_context.player_texture,
        },
    };

    player_init(p);
    
    spawner_monster_init(&app->spawner_monster, &app->game_state);
    spawner_coin_init(&app->spawner_coin, &app->game_state);
    
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
        app->game_state.dt = frame_time;
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
                if (e.type == SDL_WINDOWEVENT) {
                    int width, height;
                    SDL_GetWindowSize(app->renderer.sdl_window, &width, &height);
                    constants->screen_width = width;
                    constants->screen_height = height;
                }
            }

            app->accumilator -= TIME_STEP;
        }
        
        spawner_update(&app->spawner_monster.spawner, &app->game_state);
        spawner_update(&app->spawner_coin.spawner, &app->game_state);


        entity_pool_update(&app->entity_pool, &app->game_state);

        hud_update(&app->hud, &app->drawing_context);

        renderer_clear(&app->renderer);

        app->drawing_context.bg_scroll_y += 10 * app->dt;
        if (app->drawing_context.bg_scroll_y >= 64.0f) {
            app->drawing_context.bg_scroll_y = 0;
        }
        
        for (int y = -1; y < DISPLAY_HEIGHT / 64; y++) {
            for (int x = 0; x < DISPLAY_WIDTH / 128; x++) {
                renderer_draw_p(&app->renderer,
                                 app->drawing_context.bg_texture,
                                 (SDL_Rect) {0, 0, 128, 64}, 
                                 x * 128,
                                 y*64 + app->drawing_context.bg_scroll_y
                );
            }
        }
        
        entity_pool_draw(&app->entity_pool, &app->drawing_context);

        hud_draw(&app->hud, &app->drawing_context);

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

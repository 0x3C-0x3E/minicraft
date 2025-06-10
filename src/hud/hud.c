#include "hud.h"

void hud_init(Hud * hud) {
    hud->health = 10;
    hud->max_health = 100;

    hud->power = 0;
    hud->max_power = 100;

    hud->is_start = false;
    hud->is_game_over = false;
}

void hud_update(Hud * hud, DrawingContext * drawing_context) {
    // idk dont think i need this
}

void hud_draw(Hud * hud, DrawingContext * drawing_context) {
    // actual hud

    renderer_draw(drawing_context->renderer, drawing_context->hud_texture, (SDL_Rect) {0, 16, 48, 16}, 0, DISPLAY_HEIGHT - 24);
    for (int i = 0; i < 23; i++) {
        float p = (float) i / 23;
        float p2 = (float) hud->health / hud->max_health;
        if (p >= p2) {
            break;
        }
        renderer_draw(drawing_context->renderer, drawing_context->hud_texture, (SDL_Rect) {48, 24, 1, 2}, 20 + i, DISPLAY_HEIGHT - 24 + 8);
    }

    for (int i = 0; i < 16; i++) {
        float p = (float) i / 16;
        float p2 = (float) hud->power / hud->max_power;
        if (p >= p2) {
            break;
        }
        renderer_draw(drawing_context->renderer, drawing_context->hud_texture, (SDL_Rect) {48, 29, 1, 1}, 24 + i, DISPLAY_HEIGHT - 24 + 13);
    }

    
    // middle text
    if (hud->is_start) {
        renderer_draw(drawing_context->renderer, drawing_context->hud_texture, (SDL_Rect) {0, 8, 48, 8}, DISPLAY_WIDTH / 2 - 24 , DISPLAY_HEIGHT / 2 - 4);
    }
    if (hud->is_game_over) {
        renderer_draw(drawing_context->renderer, drawing_context->hud_texture, (SDL_Rect) {0, 0, 72, 8}, DISPLAY_WIDTH / 2 - 36, DISPLAY_HEIGHT / 2 - 4);
    }
}

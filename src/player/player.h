#pragma once
#include <stdbool.h>
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/entity_pool.h"

typedef struct Player {
    Entity entity;
    
    int speed;
    bool firing;
    float reload_timer;
    float max_reload_timer;

    float animation_counter;
    float max_animation_counter;

    SDL_Rect booster_rect;

    int health;

} Player;

void player_init(Player * player);

void player_update(Player * player, GameState * game_state);

void player_draw(Player * player, DrawingContext * drawing_context);

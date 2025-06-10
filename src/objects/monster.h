#pragma once
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/game_state.h"
#include "../entity_pool/entity_pool.h"
#include "../utils.h"
#include <stdbool.h>

typedef struct Monster {
    Entity entity; 
    int speed;
    float animation_counter;
    float max_animation_counter;

    bool is_exploding;

    float fire_counter;
    float max_fire_counter;
} Monster;

void monster_init(Monster * monster);

void monster_update(Monster * monster, GameState * game_state);

void monster_update_animation(Monster * monster, GameState * game_state);

void monster_update_fire(Monster * monster, GameState * game_state);

void monster_update_velocity(Monster * monster, GameState * game_state);

void monster_update_check_for_collision(Monster * monster, GameState * game_state);

void monster_draw(Monster * monster, DrawingContext * drawing_context);

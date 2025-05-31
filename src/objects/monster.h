#pragma once
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/game_state.h"
#include "../entity_pool/entity_pool.h"
#include <stdbool.h>

typedef struct Monster {
    Entity entity; 
    int speed;
} Monster;

void monster_init(Monster * monster);

void monster_update(Monster * monster, GameState * game_state);

void monster_draw(Monster * monster, DrawingContext * drawing_context);

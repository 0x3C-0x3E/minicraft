#pragma once
#include <stdbool.h>
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/entity_pool.h"

typedef struct Player {
    Entity entity;

    int speed;

} Player;

void player_init(Player * player);

void player_update(Player * player, GameState * game_state);

void player_draw(Player * player, DrawingContext * drawing_context);

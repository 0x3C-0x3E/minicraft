#pragma once
#include "../entity/entity.h"
#include <stdbool.h>

typedef struct Player {
    Entity entity;
} Player;

void player_init(Player * player);

void player_update(Player * player, float dt);

void player_draw(Player * player, DrawingContext * drawing_context);

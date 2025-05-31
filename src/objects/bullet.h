#pragma once
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/game_state.h"
#include "../entity_pool/entity_pool.h"
#include <stdbool.h>

typedef struct Bullet {
    Entity entity;
} Bullet;

void bullet_update(Bullet * bullet, GameState * game_state);

void bullet_draw(Bullet * bullet, DrawingContext * drawing_context);

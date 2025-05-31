#pragma once
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/game_state.h"
#include "../entity_pool/entity_pool.h"
#include <stdbool.h>

typedef struct Cactus {
    Entity entity;
    bool has_stings;
} Cactus;

void cactus_init(Cactus * cactus);

void cactus_update(Cactus * cactus, GameState * game_state);

void cactus_draw(Cactus * cactus, DrawingContext * drawing_context);

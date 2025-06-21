#pragma once
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/game_state.h"
#include "../entity_pool/entity_pool.h"
#include <stdbool.h>

typedef struct Coin {
    Entity entity;
    float speed;
    
} Coin;

void coin_init(Coin * coin, GameState * game_state);

void coin_update(Coin * coin, GameState * game_state);

void coin_draw(Coin * coin, DrawingContext * drawing_context);

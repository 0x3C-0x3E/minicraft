#pragma once
typedef struct EntityPool EntityPool;

#include "entity_pool.h"
#include "../hud/hud.h"
#include "../renderer/drawing_context.h"

typedef struct GameState {
    float dt;
    struct EntityPool * entity_pool;
    Hud * hud;
    DrawingContext * drawing_context;
} GameState;

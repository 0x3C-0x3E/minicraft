#pragma once
typedef struct EntityPool EntityPool;

#include "entity_pool.h"
#include "../renderer/drawing_context.h"

typedef struct GameState {
    float dt;
    struct EntityPool * entity_pool;
    DrawingContext * drawing_context;
} GameState;

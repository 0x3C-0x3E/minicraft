#pragma once
typedef struct EntityPool EntityPool;

#include "entity_pool.h"

typedef struct GameState {
    float dt;
    struct EntityPool * entity_pool;
} GameState;

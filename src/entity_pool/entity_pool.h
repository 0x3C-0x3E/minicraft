#pragma once
typedef struct Entity Entity;
typedef struct GameState GameState;


#include "../entity/entity.h"
#include "game_state.h"
#include "../constants.h"

#include "../player/player.h"
#include "../objects/cactus.h"

#include "../renderer/drawing_context.h"


typedef struct Cactus Cactus;
typedef struct Player Player;

enum EntityType {
   Type_Entity,
   Type_Cactus,
   Type_Player,
}; 

typedef struct EntityPool {
    unsigned int entity_count;
    void * entities[MAX_ENTITY_COUNT];

    enum EntityType entity_map[MAX_ENTITY_COUNT];

} EntityPool;

void * entity_pool_add_entity(EntityPool * entity_pool, enum EntityType entity_type);

void entity_pool_remove_entity(EntityPool * entity_pool, void * Entity);

void entity_pool_clear(EntityPool * entity_pool);

void entity_pool_update(EntityPool * entity_pool, GameState * game_state);

void entity_pool_draw(EntityPool * entity_pool, DrawingContext * drawing_context);

void entity_pool_get_entities(EntityPool * entity_pool, void * entities[MAX_ENTITY_COUNT]);

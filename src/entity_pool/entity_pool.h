#pragma once
typedef struct Entity Entity;
typedef struct GameState GameState;


#include "../entity/entity.h"
#include "game_state.h"
#include "../constants.h"

#include "../player/player.h"
#include "../objects/cactus.h"
#include "../objects/bullet.h"
#include "../objects/monster.h"
#include "../objects/coin.h"

#include "../renderer/drawing_context.h"


enum EntityType {
   Type_Entity,
   Type_Cactus,
   Type_Player,
   Type_Bullet,
   Type_Monster,
   Type_Coin,
}; 

typedef struct EntityPool {
    unsigned int entity_count;
    void * entities[MAX_ENTITY_COUNT];

    enum EntityType entity_map[MAX_ENTITY_COUNT];

    int kill_bitmask[MAX_ENTITY_COUNT];

} EntityPool;

void * entity_pool_add_entity(EntityPool * entity_pool, enum EntityType entity_type);

int entity_pool_get_index(EntityPool * entity_pool, void * entity);

void entity_pool_mark_entity_for_removal(EntityPool * entity_pool, unsigned int index);

void entity_pool_remove_entity(EntityPool * entity_pool, unsigned int index);

void entity_pool_clear(EntityPool * entity_pool);

void entity_pool_update(EntityPool * entity_pool, GameState * game_state);

void entity_pool_draw(EntityPool * entity_pool, DrawingContext * drawing_context);


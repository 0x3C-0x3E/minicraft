#pragma once
#include "../entity/entity.h"
#include "../constants.h"

#include "../player/player.h"
#include "../objects/cactus.h"

struct Entity;
struct Cactus;
struct Player;

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

void entity_pool_update(EntityPool * entity_pool);

void entity_pool_draw(EntityPool * entity_pool, DrawingContext * drawing_context);

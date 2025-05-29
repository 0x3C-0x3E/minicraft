#pragma once
#include "../entity/entity.h"
#include "../constants.h"

enum EntityType {
   Type_Entity
}; 

typedef struct EntityPool {
    unsigned int entity_count;
    void * entities[MAX_ENTITY_COUNT];

    enum EntityType entity_map[MAX_ENTITY_COUNT];

} EntityPool;

void * entity_pool_add_entity(EntityPool * entity_pool, enum EntityType entity_type, int x, int y, SDL_Rect img_rect, SDL_Texture * texture);

void entity_pool_remove_entity(EntityPool * entity_pool, void * Entity);

void entity_pool_clear(EntityPool * entity_pool);

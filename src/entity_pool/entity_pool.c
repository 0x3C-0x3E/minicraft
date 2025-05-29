#include "entity_pool.h"

void * entity_pool_add_entity(EntityPool * entity_pool, enum EntityType entity_type, int x, int y, SDL_Rect img_rect, SDL_Texture * texture) {
    switch (entity_type) {
        case Type_Entity:
            entity_pool->entities[entity_pool->entity_count] = malloc(sizeof(Entity));
            *(Entity * ) entity_pool->entities[entity_pool->entity_count] = (Entity) {
                .x = x,
                .y = y,
                .img_rect = img_rect,
                .texture = texture,
            };
            entity_pool->entity_map[entity_pool->entity_count] = Type_Entity;
            break; 
    }

    entity_pool->entity_count ++;
    
    return entity_pool->entities[entity_pool->entity_count];
}

void entity_pool_clear(EntityPool * entity_pool) {
    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        free(entity_pool->entities[i]);
    }
}

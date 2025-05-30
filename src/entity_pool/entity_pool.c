#include "entity_pool.h"

void * entity_pool_add_entity(EntityPool * entity_pool, enum EntityType entity_type) {
    void * return_entity;
    switch (entity_type) {
        case Type_Entity:
            entity_pool->entities[entity_pool->entity_count] = malloc(sizeof(Entity));
            entity_pool->entity_map[entity_pool->entity_count] = Type_Entity;
            break;
        case Type_Cactus:
            entity_pool->entities[entity_pool->entity_count] = malloc(sizeof(Cactus));
            entity_pool->entity_map[entity_pool->entity_count] = Type_Cactus;
            break;
        case Type_Player:
            entity_pool->entities[entity_pool->entity_count] = malloc(sizeof(Player));
            entity_pool->entity_map[entity_pool->entity_count] = Type_Player;
            break;
    }
    
    // the order is important here, messed this up already (:
    return_entity = entity_pool->entities[entity_pool->entity_count];
    entity_pool->entity_count ++;
    return return_entity;
}

void entity_pool_clear(EntityPool * entity_pool) {
    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        free(entity_pool->entities[i]);
    }
}


void entity_pool_update(EntityPool * entity_pool, float dt) {
    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        switch (entity_pool->entity_map[i]) {
            case Type_Entity:
                entity_update((Entity * )entity_pool->entities[i], dt);
                break;
            case Type_Cactus:
                cactus_update((Cactus * )entity_pool->entities[i], dt);
                break;
            case Type_Player:
                player_update((Player * )entity_pool->entities[i], dt);
                break;
        }
    }
}

void entity_pool_draw(EntityPool * entity_pool, DrawingContext * drawing_context) {
    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        switch (entity_pool->entity_map[i]) {
            case Type_Entity:
                entity_draw((Entity * )entity_pool->entities[i], drawing_context);
                break;
            case Type_Cactus:
                cactus_draw((Cactus * )entity_pool->entities[i], drawing_context);
                break;
            case Type_Player:
                player_draw((Player * )entity_pool->entities[i], drawing_context);
                break;
        }
    }
}

#include "entity_pool.h"
#include <stdio.h>

void * entity_pool_add_entity(EntityPool * entity_pool, enum EntityType entity_type) {
    void * return_entity;
    if (entity_pool->entity_count == MAX_ENTITY_COUNT) {
        printf("Reached Entity Limit!\n");
        return NULL;
    }
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
        case Type_Bullet:
            entity_pool->entities[entity_pool->entity_count] = malloc(sizeof(Bullet));
            entity_pool->entity_map[entity_pool->entity_count] = Type_Bullet;
            break;
        case Type_Monster:
            entity_pool->entities[entity_pool->entity_count] = malloc(sizeof(Monster));
            entity_pool->entity_map[entity_pool->entity_count] = Type_Monster;
            break;
    }
    
    // the order is important here, messed this up already (:
    return_entity = entity_pool->entities[entity_pool->entity_count];
    entity_pool->entity_count ++;
    return return_entity;
}

void entity_pool_mark_entity_for_removal(EntityPool * entity_pool, unsigned int index) {
    entity_pool->kill_bitmask[index] = 1;
}

int entity_pool_get_index(EntityPool * entity_pool, void * entity) {
    int index = 0;
    for (unsigned int i = index + 1; i < entity_pool->entity_count; i++) {
        if (entity == entity_pool->entities[i]) {
            index = i;
        }
    }
    return index;
}

void entity_pool_remove_entity(EntityPool * entity_pool, unsigned int index) {
    
    if (index >= entity_pool->entity_count) return;

    free(entity_pool->entities[index]);

    for (unsigned int i = index + 1; i < entity_pool->entity_count; i++) {
        entity_pool->entities[i - 1] = entity_pool->entities[i];
        entity_pool->entity_map[i - 1] = entity_pool->entity_map[i];
    }

    // entity_pool->entities[entity_pool->entity_count - 1] = NULL;
    // entity_pool->entity_map[entity_pool->entity_count - 1] = 0;

    entity_pool->entity_count --;
}

void entity_pool_clear(EntityPool * entity_pool) {
    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        free(entity_pool->entities[i]);
    }
}


void entity_pool_update(EntityPool * entity_pool, GameState * game_state) {
    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        switch (entity_pool->entity_map[i]) {
            case Type_Entity:
                entity_update((Entity * )entity_pool->entities[i]);
                break;
            case Type_Cactus:
                cactus_update((Cactus * )entity_pool->entities[i], game_state);
                break;
            case Type_Player:
                player_update((Player * )entity_pool->entities[i], game_state);
                break;
            case Type_Bullet:
                bullet_update((Bullet * )entity_pool->entities[i], game_state);
                break;
            case Type_Monster:
                monster_update((Monster * )entity_pool->entities[i], game_state);
                break;
        }
    }

    for (unsigned int i = 0; i < entity_pool->entity_count; i++) {
        if (entity_pool->kill_bitmask[i] == 1) {
            entity_pool_remove_entity(entity_pool, i);
            entity_pool->kill_bitmask[i] = 0;
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
            case Type_Bullet:
                bullet_draw((Bullet * )entity_pool->entities[i], drawing_context);
                break;
            case Type_Monster:
                monster_draw((Monster * )entity_pool->entities[i], drawing_context);
                break;
        }
    }
}


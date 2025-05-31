#include "monster.h"
#include "../utils.h"
#include <stdio.h>

void monster_init(Monster * monster) {
    monster->speed = -100;
    monster->entity.x_vel = -monster->speed;

    monster->entity.y_vel = 2.0f;

}

void monster_update(Monster * monster, GameState * game_state) {

    monster->entity.x += monster->entity.x_vel * game_state->dt;
    monster->entity.y += monster->entity.y_vel * game_state->dt;

    if (monster->entity.x < 0 || monster->entity.x + 16 > DISPLAY_WIDTH) {
        monster->entity.x_vel *= -1;
        monster->entity.y_vel *= 1.1;

        if (monster->entity.x < 0) {
            monster->entity.x = 0;
        } else {
            monster->entity.x = DISPLAY_WIDTH - 16;
        }
    }
    
    if (monster->entity.y >= DISPLAY_HEIGHT) {
        entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )monster));
        printf("Game Over!\n");
    }

    for (unsigned int i = 0; i < game_state->entity_pool->entity_count; i ++) {
        if (game_state->entity_pool->entity_map[i] == Type_Bullet) {
            Bullet * b = (Bullet * ) game_state->entity_pool->entities[i];
            if (rects_collide(monster->entity.x, monster->entity.y, 16, 16, b->entity.x, b->entity.y, 16, 16)) {
                entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )monster));
            }
        }
    }
}

void monster_draw(Monster * monster, DrawingContext * drawing_context) {
    entity_draw(&monster->entity, drawing_context);
}

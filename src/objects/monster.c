#include "monster.h"
#include "../utils.h"
#include <stdio.h>

void monster_init(Monster * monster) {
    monster->speed = -100;
    monster->entity.x_vel = -monster->speed;

    monster->entity.y_vel = 2.0f;
    
    monster->animation_counter = 0.0f;
    monster->max_animation_counter = 0.1f;

    monster->is_exploding = false;
}


void monster_update(Monster * monster, GameState * game_state) {
    
    monster_update_animation(monster, game_state);

    monster->entity.x += monster->entity.x_vel * game_state->dt;
    monster->entity.y += monster->entity.y_vel * game_state->dt;

    if (monster->is_exploding)  {
        return;
    }

    monster_update_velocity(monster, game_state);

    monster_update_check_for_collision(monster, game_state);
    
}

void monster_update_animation(Monster * monster, GameState * game_state) {
    monster->animation_counter += 1.0f * game_state->dt;


    if (!(monster->animation_counter >= monster->max_animation_counter)) {
        return;
    }

    monster->animation_counter = 0;
    monster->entity.img_rect.x += 16;


    Bullet * b = entity_pool_add_entity(game_state->entity_pool, Type_Bullet);
    *b = (Bullet) {
        .entity = {
            .x = monster->entity.x,
            .y = monster->entity.y,
            .img_rect = (SDL_Rect) {0, 0, 16, 16}, 
            .texture = game_state->drawing_context->monster_bullet_texture,
        },
    };

    bullet_init(b, game_state, 75);

    
    if (monster->is_exploding) {
        if (monster->entity.img_rect.x >= 64) {
            // finished explosion animation
            entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )monster));
        }
    } else {
        if (monster->entity.img_rect.x >= 80) {
            monster->entity.img_rect.x = 0;
        }
    }

}

void monster_update_velocity(Monster * monster, GameState * game_state) {
    if (monster->entity.x < 0 || monster->entity.x + 16 > DISPLAY_WIDTH) {
        monster->entity.x_vel *= -1;
        monster->entity.y_vel *= 1.1;

        if (monster->entity.x < 0) {
            monster->entity.x = 0;
        } else {
            monster->entity.x = DISPLAY_WIDTH - 16;
        }
    }
}

void monster_update_check_for_collision(Monster * monster, GameState * game_state) {
    if (monster->entity.y >= DISPLAY_HEIGHT) {
        entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )monster));
        printf("Game Over!\n");
    }

    for (unsigned int i = 0; i < game_state->entity_pool->entity_count; i ++) {
        if (game_state->entity_pool->entity_map[i] == Type_Bullet) {
            Bullet * b = (Bullet * ) game_state->entity_pool->entities[i];
            
            // quick fix for monsters to not kill themselves after shooting a bullet
            // cause you cant hit yourself if the bullet's going in the other direction
            if (b->entity.y_vel > 0) {
                continue;
            }

            if (rects_collide(monster->entity.x, monster->entity.y, 16, 16, b->entity.x, b->entity.y, 16, 16)) {
                entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )b));
                monster->is_exploding = true;
                monster->entity.img_rect = (SDL_Rect) {0, 0, 16, 16};
                monster->entity.texture = game_state->drawing_context->explosion_texture;
            }
        }
    }
}

void monster_draw(Monster * monster, DrawingContext * drawing_context) {
    entity_draw(&monster->entity, drawing_context);
}

#include "bullet.h"
#include "../utils.h"
#include <stdio.h>

void bullet_init(Bullet * bullet, GameState * game_state, float y_vel) {
    bullet->entity.y_vel = y_vel;
    bullet->animation_counter = 0.0f;
    bullet->max_animation_counter = 0.3f;
}

void bullet_update(Bullet * bullet, GameState * game_state) {
    
    bullet_update_animation(bullet, game_state);

    bullet->entity.y += bullet->entity.y_vel * game_state->dt;

    bullet_update_check_collision(bullet, game_state);

    if (bullet->entity.y <= 0 || bullet->entity.y >= DISPLAY_HEIGHT) {
        entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )bullet));
    }

}

void bullet_update_animation(Bullet * bullet, GameState * game_state) {
    bullet->animation_counter += 1.0f * game_state->dt;
    if (bullet->animation_counter <= bullet->max_animation_counter) {
        return;
    }

    bullet->animation_counter = 0.0f;
    
    //very scuffed but works
    if (bullet->entity.img_rect.w == 8) {
        bullet->entity.img_rect.x = (bullet->entity.img_rect.x == 0) ?  8 : 0;
    } else {
        bullet->entity.img_rect.x = (bullet->entity.img_rect.x == 0) ? 16 : 0;
    }
}

void bullet_update_check_collision(Bullet * bullet, GameState * game_state) {
    for (unsigned int i = 0; i < game_state->entity_pool->entity_count; i ++) {
        void * entity = game_state->entity_pool->entities[i];
        if (game_state->entity_pool->entity_map[i] == Type_Monster) {
            Monster * monster = (Monster * ) entity;
            if (bullet->entity.y_vel > 0) {
                continue;
            }

            if (rects_collide(bullet->entity.x, bullet->entity.y, bullet->entity.img_rect.w, bullet->entity.img_rect.h, monster->entity.x, monster->entity.y, 16, 16)) {
                monster->is_exploding = true;
                monster->entity.img_rect = (SDL_Rect) {0, 0, 16, 16};
                monster->entity.texture = game_state->drawing_context->explosion_texture;
                entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, bullet));
            }
        } else if (game_state->entity_pool->entity_map[i] == Type_Player) {
            Player * player = (Player * ) entity;
            if (bullet->entity.y_vel < 0) {
                continue;
            }

            if (rects_collide(bullet->entity.x, bullet->entity.y, bullet->entity.img_rect.w, bullet->entity.img_rect.h, player->entity.x, player->entity.y, 16, 16)) {
                printf("Got hit!\n");
                // TODO: lower health
            }
        }
    }
}



void bullet_draw(Bullet * bullet, DrawingContext * drawing_context) {
    entity_draw(&bullet->entity, drawing_context);
};

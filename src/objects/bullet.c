#include "bullet.h"

void bullet_init(Bullet * bullet, GameState * game_state, float y_vel) {
    bullet->entity.y_vel = y_vel;
}

void bullet_update(Bullet * bullet, GameState * game_state) {

    bullet->entity.y += bullet->entity.y_vel * game_state->dt;

    if (bullet->entity.y <= 0 || bullet->entity.y >= DISPLAY_HEIGHT) {
        entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, (void * )bullet));
    }
}


void bullet_draw(Bullet * bullet, DrawingContext * drawing_context) {
    entity_draw(&bullet->entity, drawing_context);
}

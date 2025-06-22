#include "coin.h"
#include "../utils.h"
#include <stdio.h>

void coin_init(Coin * coin, GameState * game_state) {
    coin->speed = 50;
    coin->entity.y_vel = coin->speed;
}

void coin_update(Coin * coin, GameState * game_state) {

    coin->entity.x += coin->entity.x_vel * game_state->dt;
    coin->entity.y += coin->entity.y_vel * game_state->dt;

    for (int i = 0; i < game_state->entity_pool->entity_count; i++) {
        void * entity = game_state->entity_pool->entities[i];
        if (game_state->entity_pool->entity_map[i] == Type_Player) {
            Player * player = (Player * ) entity;

            if (rects_collide(coin->entity.x, coin->entity.y, coin->entity.img_rect.w, coin->entity.img_rect.h, player->entity.x, player->entity.y, 16, 16)) {
                game_state->hud->score += 15;
                entity_pool_mark_entity_for_removal(game_state->entity_pool, entity_pool_get_index(game_state->entity_pool, coin));
            }
        }
    }
}

void coin_draw(Coin * coin, DrawingContext * drawing_context) {
    entity_draw(&coin->entity, drawing_context);
}

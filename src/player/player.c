#include "player.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include <wchar.h>

void player_init(Player * player) {
    player->speed = 100;
    player->firing = false;
}

void player_update(Player * player, GameState * game_state) {
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_D]) {
        player->entity.x_vel = player->speed;
    } else if (keystate[SDL_SCANCODE_A]) {
        player->entity.x_vel = -player->speed;
    } else { 
        player->entity.x_vel = 0;
    }

    if (keystate[SDL_SCANCODE_SPACE] && !player->firing) {
        Bullet * c = entity_pool_add_entity(game_state->entity_pool, Type_Bullet);
        *c = (Bullet) {
            .entity = {
                .x = player->entity.x,
                .y = player->entity.y,
                .img_rect = (SDL_Rect) {0, 0, 16, 16}, 
                .texture = game_state->drawing_context->bullet_texture,
            },

        };
        player->firing = true;
    } else if (!keystate[SDL_SCANCODE_SPACE] && player->firing) {
        player->firing = false;
    }

    
    for (unsigned int i = 0; i < game_state->entity_pool->entity_count; i++) {
        if (game_state->entity_pool->entity_map[i] == Type_Cactus) {
            Cactus * c = (Cactus * ) game_state->entity_pool->entities[i];
            // entity_pool_mark_entity_for_removal(game_state->entity_pool, i);
        }
    }

    player->entity.x += player->entity.x_vel * game_state->dt;

}

void player_draw(Player * player, DrawingContext * drawing_context) {
    entity_draw(&player->entity, drawing_context);
}

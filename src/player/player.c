#include "player.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <wchar.h>

void player_init(Player * player) {
    player->speed = 100;
    player->firing = false;

    player->animation_counter = 0;
    player->max_animation_counter = 0.5f;
    player->booster_rect = (SDL_Rect) {0, 0, 16, 16};
}

void player_update(Player * player, GameState * game_state) {
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_D]) {
        player->entity.x_vel = player->speed;
        player->entity.img_rect = (SDL_Rect) {32, 0, 16, 16};
    } else if (keystate[SDL_SCANCODE_A]) {
        player->entity.x_vel = -player->speed;
        player->entity.img_rect = (SDL_Rect) {0, 0, 16, 16};
    } else { 
        player->entity.img_rect = (SDL_Rect) {16, 0, 16, 16};
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

    player->entity.x += player->entity.x_vel * game_state->dt;

    if (player->entity.x <= 0) {
        player->entity.x = 0;
    }

    if (player->entity.x >= DISPLAY_WIDTH - 16) {
        player->entity.x = DISPLAY_WIDTH - 16;
    }

    player->animation_counter += 1 + game_state->dt;
    if (player->animation_counter >= player->max_animation_counter) {
        player->animation_counter = 0;
        player->booster_rect.x = (player->booster_rect.x == 0) ? 16 : 0;
    }

}

void player_draw(Player * player, DrawingContext * drawing_context) {
    entity_draw(&player->entity, drawing_context);

    renderer_draw(drawing_context->renderer, drawing_context->booster_texture, player->booster_rect, player->entity.x, player->entity.y + 16);
}

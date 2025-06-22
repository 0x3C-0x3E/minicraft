#include "player.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>

void player_init(Player * player) {
    player->speed = 100;
    player->firing = false;

    player->animation_counter = 0;
    player->max_animation_counter = 0.5f;
    player->booster_rect = (SDL_Rect) {0, 0, 16, 16};


    player->reload_timer = 0.0f;
    player->max_reload_timer = 1.5f;

    player->health = 100;
    player->power = 100;
}

void player_update(Player * player, GameState * game_state) {
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);
    
    bool horizontal_movement = false;
    bool vertical_movement = false;

    if (keystate[SDL_SCANCODE_D]) {
        player->entity.x_vel = player->speed;
        player->entity.img_rect = (SDL_Rect) {32, 0, 16, 16};
        horizontal_movement = true;
    } else if (keystate[SDL_SCANCODE_A]) {
        player->entity.x_vel = -player->speed;
        player->entity.img_rect = (SDL_Rect) {0, 0, 16, 16};
        horizontal_movement = true;
    } else { 
        player->entity.img_rect = (SDL_Rect) {16, 0, 16, 16};
        player->entity.x_vel = 0;
    }


    if (keystate[SDL_SCANCODE_W]) {
        player->entity.y_vel = -player->speed;
        vertical_movement = true;
    } else if (keystate[SDL_SCANCODE_S]) {
        player->entity.y_vel = player->speed;
        vertical_movement = true;
    } else {
        player->entity.y_vel = 0;
    }


    if (horizontal_movement && vertical_movement) {
        // yes i am too lazy to google how to import math.h in c with sin and pi so magic number it is (:
        // for later (or probably never) math.sin((math.pi / 180) * 45)
        player->entity.x_vel *= 0.7071067811865475;
        player->entity.y_vel *= 0.7071067811865475;
    }

    player->reload_timer += 1 * game_state->dt;
    player->power = (int) ((float)player->reload_timer / player->max_reload_timer * 100);

    if (keystate[SDL_SCANCODE_SPACE] && !player->firing && player->reload_timer >= player->max_reload_timer / 2) {
        player_shoot(player, game_state);
    } else if (!keystate[SDL_SCANCODE_SPACE] && player->firing) {
        player->firing = false;
    }

    player->entity.x += player->entity.x_vel * game_state->dt;
    player->entity.y += player->entity.y_vel * game_state->dt;

    if (player->entity.x <= 0) {
        player->entity.x = 0;
    }
    if (player->entity.x >= DISPLAY_WIDTH - 16) {
        player->entity.x = DISPLAY_WIDTH - 16;
    }

    player->entity.y = (player->entity.y <= 0) ? 0 : player->entity.y;
    player->entity.y = (player->entity.y >= DISPLAY_HEIGHT-16) ? DISPLAY_HEIGHT-16 : player->entity.y;

    player->animation_counter += 1 + game_state->dt;
    if (player->animation_counter >= player->max_animation_counter) {
        player->animation_counter = 0;
        player->booster_rect.x = (player->booster_rect.x == 0) ? 16 : 0;
    }

    game_state->hud->health = player->health;
    if (player->health <= 0) {
        game_state->hud->is_game_over = true;
    }

    game_state->hud->power = player->power;

}

void player_shoot(Player * player, GameState * game_state) {
    // if we only reloaded to half of the reload_timer, we only shoot one bullet
    int number_of_bullets = (player->reload_timer <= player->max_reload_timer) ? 1 : 2;
    for (int i = 0; i < number_of_bullets; i++) {
        Bullet * b = entity_pool_add_entity(game_state->entity_pool, Type_Bullet);
        *b = (Bullet) {
            .entity = {
                .x = player->entity.x + i * 8,
                .y = player->entity.y,
                .img_rect = (SDL_Rect) {0, 0, 8, 16}, 
                .texture = game_state->drawing_context->bullet_texture,
            },
        };

        bullet_init(b, game_state, -100, Player_Bullet);
    }
    player->firing = true;
    player->reload_timer = 0;
}

void player_draw(Player * player, DrawingContext * drawing_context) {
    entity_draw(&player->entity, drawing_context);

    renderer_draw(drawing_context->renderer, drawing_context->booster_texture, player->booster_rect, player->entity.x, player->entity.y + 16);
}

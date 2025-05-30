#include "player.h"
#include <SDL2/SDL_keyboard.h>
#include <stdio.h>
#include <wchar.h>

void player_init(Player * player) {

}

void player_update(Player * player, GameState * game_state) {
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_D]) {
        player->entity.x_vel = 50;
    } else if (keystate[SDL_SCANCODE_A]) {
        player->entity.x_vel = -50;
    } else {
        player->entity.x_vel = 0;
    }
    
    for (unsigned int i = 0; i < game_state->entity_pool->entity_count; i++) {
        if (game_state->entity_pool->entity_map[i] == Type_Cactus) {
            Cactus * c = (Cactus * ) game_state->entity_pool->entities[i];
            printf("Cactus X: %f\n", c->entity.x);
        }
    }

    player->entity.x += player->entity.x_vel * game_state->dt;

}

void player_draw(Player * player, DrawingContext * drawing_context) {
    entity_draw(&player->entity, drawing_context);
}

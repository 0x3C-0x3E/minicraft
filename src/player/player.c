#include "player.h"
#include <SDL2/SDL_keyboard.h>
#include <wchar.h>

void player_init(Player * player) {

}

void player_update(Player * player, float dt) {
    const Uint8 * keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_D]) {
        player->entity.x_vel = 50;
    } else if (keystate[SDL_SCANCODE_A]) {
        player->entity.x_vel = -50;
    } else {
        player->entity.x_vel = 0;
    }


    player->entity.x += player->entity.x_vel * dt;

}

void player_draw(Player * player, DrawingContext * drawing_context) {
    entity_draw(&player->entity, drawing_context);
}

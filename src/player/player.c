#include "player.h"

void player_init(Player * player) {

}

void player_update(Player * player) {

}

void player_draw(Player * player, DrawingContext * drawing_context) {
    entity_draw(&player->entity, drawing_context);
}

#include "monster.h"

void monster_init(Monster * monster) {
    monster->speed = -100;
    monster->entity.x_vel = -monster->speed;
}

void monster_update(Monster * monster, GameState * game_state) {
    monster->entity.x += monster->entity.x_vel * game_state->dt;
    if (monster->entity.x < 0 || monster->entity.x + 16 > DISPLAY_WIDTH) {
        monster->entity.x_vel *= -1;
    }
}

void monster_draw(Monster * monster, DrawingContext * drawing_context) {
    entity_draw(&monster->entity, drawing_context);
}

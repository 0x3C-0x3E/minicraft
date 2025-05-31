#include "spawner_monster.h"

void spawner_monster_init(SpawnerMonster * spawner_monster, GameState * game_state) {
    spawner_monster->max_spawner_counter = 5.5f;
    spawner_monster->spawner_counter = 0.0f;
}

void spawner_monster_update(SpawnerMonster * spawner_monster, GameState * game_state) {
    spawner_monster->spawner_counter += 1 * game_state->dt;

    if (spawner_monster->spawner_counter >= spawner_monster->max_spawner_counter) {
        Monster * m = entity_pool_add_entity(game_state->entity_pool, Type_Monster);
        *m = (Monster) {
            .entity = {
                .x = DISPLAY_WIDTH / 2,
                .y = 50.0f,
                .img_rect = (SDL_Rect) {0, 0, 16, 16},
                .texture = game_state->drawing_context->monster_texture,
            },
        };
        monster_init(m);

        spawner_monster->spawner_counter = 0;
    }
}

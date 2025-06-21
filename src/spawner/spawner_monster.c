#include "spawner_monster.h"
#include "../utils.h"

void spawner_monster_init(SpawnerMonster * spawner_monster, GameState * game_state) {
    spawner_monster->spawner = (Spawner) {
        .max_spawner_counter = 5,
        .spawner_counter = 0,
        .spawing_func = spawner_monster_spawn_monster,
        .wave_size = 4,
    };
}


void spawner_monster_spawn_monster(GameState * game_state, int x, int y) {
    Monster * m = entity_pool_add_entity(game_state->entity_pool, Type_Monster);
    *m = (Monster) {
        .entity = {
            .x = x,
            .y = y,
            .img_rect = (SDL_Rect) {0, 0, 16, 16},
            .texture = game_state->drawing_context->monster_texture,
        },
    };
    monster_init(m);
}

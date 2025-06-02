#include "spawner_monster.h"
#include <stdio.h>

void spawner_monster_init(SpawnerMonster * spawner_monster, GameState * game_state) {
    spawner_monster->max_spawner_counter = 5.5f;
    spawner_monster->spawner_counter = 0.0f;
    
    spawner_monster->wave_size = 5;
}

void spawner_monster_update(SpawnerMonster * spawner_monster, GameState * game_state) {
    spawner_monster->spawner_counter += 1 * game_state->dt;

    if (spawner_monster->spawner_counter >= spawner_monster->max_spawner_counter) {
        spawner_monster_spawn_wave(spawner_monster, game_state);

        spawner_monster->spawner_counter = 0;
    }
}

void spawner_monster_spawn_wave(SpawnerMonster * spawner_monster, GameState * game_state) {
    for (int i = 0; i < spawner_monster->wave_size; i++) {
        spawner_monster_spawn_monster(spawner_monster, game_state, 24 * i, 24);
    }
}

void spawner_monster_spawn_monster(SpawnerMonster * spawner_monster, GameState * game_state, int x, int y) {
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

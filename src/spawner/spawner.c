#include "spawner.h"

void spawner_update(Spawner * spawner, GameState * game_state) {
    spawner->spawner_counter += 1 * game_state->dt;

    if (spawner->spawner_counter >= spawner->max_spawner_counter) {
        spawner_spawn_wave(spawner, game_state);

        spawner->spawner_counter = 0;
    }
}

void spawner_spawn_wave(Spawner * spawner, GameState * game_state)
{
    for (int i = 0; i < spawner->wave_size; i++) {
        spawner->spawing_func(game_state, i * 16, 0);
    }
}

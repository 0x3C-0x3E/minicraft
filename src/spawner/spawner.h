#pragma once
#include "../entity_pool/entity_pool.h"

typedef struct Spawner {
    float spawner_counter;
    float max_spawner_counter;

    int wave_size;

    void (*spawing_func) (GameState * game_state, int x, int y);
} Spawner;

void spawner_update(Spawner * spawner, GameState * game_state);

void spawner_spawn_wave(Spawner * spawner, GameState * game_state);

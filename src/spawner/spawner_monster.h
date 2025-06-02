#pragma once
#include "../objects/monster.h"
#include "../entity_pool/entity_pool.h"

typedef struct SpawnerMonster {
    float spawner_counter;
    float max_spawner_counter;

    int wave_size;
} SpawnerMonster;

void spawner_monster_init(SpawnerMonster * spawner_monster, GameState * game_state);

void spawner_monster_update(SpawnerMonster * spawner_monster, GameState * game_state);

void spawner_monster_spawn_wave(SpawnerMonster * spawner_monster, GameState * game_state);

void spawner_monster_spawn_monster(SpawnerMonster * spawner_monster, GameState * game_state, int x, int y);

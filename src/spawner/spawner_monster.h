#pragma once
#include "../objects/monster.h"
#include "../entity_pool/entity_pool.h"

#include "spawner.h"
typedef struct SpawnerMonster {
   Spawner spawner; 
} SpawnerMonster;

void spawner_monster_init(SpawnerMonster * spawner_monster, GameState * game_state);

void spawner_monster_spawn_monster(GameState * game_state, int x, int y);

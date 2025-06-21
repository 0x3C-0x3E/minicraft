#pragma once
#include "../objects/coin.h"
#include "../entity_pool/entity_pool.h"

#include "spawner.h"

typedef struct SpawnerCoin {
    Spawner spawner;
} SpawnerCoin;

void spawner_coin_init(SpawnerCoin * spawner_coin, GameState * game_state);

void spawner_coin_spawn_coin(GameState * game_state, int x, int y);

#include "spawner_coin.h"

void spawner_coin_init(SpawnerCoin * spawner_coin, GameState * game_state) {
    spawner_coin->spawner = (Spawner) {
        .max_spawner_counter = 4.0f,
        .spawner_counter = 0,
        .spawing_func = spawner_coin_spawn_coin,
        .wave_size = 2,
    };
}

void spawner_coin_spawn_coin(GameState * game_state, int x, int y) {
    Coin * c = entity_pool_add_entity(game_state->entity_pool, Type_Coin);
    *c = (Coin) {
        .entity = {
            .x = x,
            .y = y,
            .img_rect = (SDL_Rect) {0, 0, 16, 16},
            .texture = game_state->drawing_context->coin_texture,
        },
    };
    coin_init(c, game_state);
}

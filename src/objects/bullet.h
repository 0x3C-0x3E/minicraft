#pragma once
#include "../entity/entity.h"
#include "../renderer/drawing_context.h"
#include "../entity_pool/game_state.h"
#include "../entity_pool/entity_pool.h"
#include <stdbool.h>

enum Bullet_Type {
    Player_Bullet,
    Monster_Bullet,
};


typedef struct Bullet {
    Entity entity;

    float animation_counter;
    float max_animation_counter;

    enum Bullet_Type bullet_type;
} Bullet;

void bullet_init(Bullet * bullet, GameState * game_state, float y_vel, enum Bullet_Type bullet_type);

void bullet_update(Bullet * bullet, GameState * game_state);

void bullet_update_animation(Bullet * bullet, GameState * game_state);

void bullet_update_check_collision(Bullet * bullet, GameState * game_state);

void bullet_draw(Bullet * bullet, DrawingContext * drawing_context);

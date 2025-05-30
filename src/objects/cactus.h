#pragma once
#include "../entity/entity.h"
#include <stdbool.h>

typedef struct Cactus {
    Entity entity;
    bool has_stings;
} Cactus;

void cactus_init(Cactus * cactus);

void cactus_update(Cactus * cactus, float dt);

void cactus_draw(Cactus * cactus, DrawingContext * drawing_context);

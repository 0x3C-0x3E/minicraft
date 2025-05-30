#include "cactus.h"
#include <stdio.h>

void cactus_init(Cactus * cactus);

void cactus_update(Cactus * cactus, GameState * game_state) {
    cactus->entity.x += 1;

    if (cactus->entity.x >= DISPLAY_WIDTH) {
        printf("Deleting Cactus!\n");
        for (unsigned int i = 0; i < game_state->entity_pool->entity_count; i ++) {
            if (game_state->entity_pool->entities[i] == cactus) {
                entity_pool_mark_entity_for_removal(game_state->entity_pool, i);
                printf("Actually deleting it!\n");
            }
        }

    }
}

void cactus_draw(Cactus * cactus, DrawingContext * drawing_context) {
    if (cactus->entity.texture == NULL) {
        printf("Invaild Texture");
    }
    entity_draw(&cactus->entity, drawing_context);
}

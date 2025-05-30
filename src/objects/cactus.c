#include "cactus.h"
#include <stdio.h>

void cactus_init(Cactus * cactus);

void cactus_update(Cactus * cactus) {
    cactus->entity.x += 1;
}

void cactus_draw(Cactus * cactus, DrawingContext * drawing_context) {
    if (cactus->entity.texture == NULL) {
        printf("Invaild Texture");
    }
    entity_draw(&cactus->entity, drawing_context);
}

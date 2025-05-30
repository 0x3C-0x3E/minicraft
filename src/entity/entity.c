#include "entity.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

void entity_init(Entity * entity, int x, int y, SDL_Rect img_rect, SDL_Texture * texture) {
    entity->x = x;
    entity->y = y;

    entity->img_rect = img_rect;
    entity->texture = texture;
}

void entity_update(Entity * entity) {
    entity->x ++;
}

void entity_draw(Entity * entity, DrawingContext * drawing_context) {
    if (entity->texture == NULL) {
        printf("INVAILD TEXTURE!\n");
    }
    renderer_draw(drawing_context->renderer, entity->texture, entity->img_rect, entity->x, entity->y);
}

#pragma once

typedef struct Entity Entity;

#include "../renderer/renderer.h"
#include "../renderer/drawing_context.h"
#include <SDL2/SDL.h>

typedef struct Entity {
   float x;
   float y;

   float x_vel;
   float y_vel;

   SDL_Rect img_rect;
   SDL_Texture * texture;
} Entity;

void entity_init(Entity * entity, int x, int y, SDL_Rect img_rect, SDL_Texture * texture);

void entity_draw(Entity * entity, DrawingContext * drawing_context);

void entity_update(Entity * entity);

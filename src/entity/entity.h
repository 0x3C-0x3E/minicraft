#pragma once
#include "../renderer/renderer.h"
#include <SDL2/SDL.h>

typedef struct Entity {
   int x;
   int y;

   SDL_Rect img_rect;
   SDL_Texture * texture;
} Entity;

void entity_init(Entity * entity, int x, int y, SDL_Rect img_rect, SDL_Texture * texture);

void entity_draw(Entity * entity, Renderer * renderer);

void entity_update(Entity * entity);

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "../constants.h"

typedef struct Renderer {
    SDL_Window * sdl_window;
    SDL_Renderer * sdl_renderer;
} Renderer;

int renderer_init(Renderer * renderer);

void renderer_clear(Renderer * renderer);

void renderer_present(Renderer * renderer);

SDL_Texture * renderer_load_texture(Renderer * renderer, const char * filepath);

void renderer_draw(Renderer * renderer,SDL_Texture * texture, SDL_Rect img_rect, float x, float y);

void renderer_draw_ex(Renderer * renderer,SDL_Texture * texture, SDL_Rect img_rect, float x, float y, bool flip_v, bool flip_h);

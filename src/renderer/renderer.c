#include "renderer.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

int renderer_init(Renderer * renderer) {

    renderer->sdl_window = SDL_CreateWindow(
        "Minicraft",
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN
    );

    if (!renderer->sdl_window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }


    renderer->sdl_renderer = SDL_CreateRenderer(renderer->sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer->sdl_renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer->sdl_renderer, 50, 50 , 50, 255);

    return 0;
}

void renderer_clear(Renderer * renderer) {
    SDL_RenderClear(renderer->sdl_renderer);
}

void renderer_present(Renderer * renderer) {
    SDL_RenderPresent(renderer->sdl_renderer);
}

SDL_Texture * renderer_load_texture(Renderer * renderer, const char * filepath) {
    SDL_Texture * texture = NULL;
    texture = IMG_LoadTexture(renderer->sdl_renderer, filepath);

    if (texture == NULL) {
        printf("Couldn no load texture!: %s\n", SDL_GetError());
    }

    return texture;
}

void renderer_draw(Renderer * renderer, SDL_Texture * texture, SDL_Rect img_rect, float x, float y) {
    SDL_Rect src;

    src.x = img_rect.x;
    src.y = img_rect.y;

    src.w = img_rect.w;
    src.h = img_rect.h;

    SDL_Rect dst;
    dst.x = x * RENDER_SCALE;
    dst.y = y * RENDER_SCALE;

    dst.w = src.w * RENDER_SCALE;
    dst.h = src.h * RENDER_SCALE;
    
    SDL_RenderCopy(renderer->sdl_renderer, texture, &src, &dst);
}

void renderer_draw_ex(Renderer * renderer,SDL_Texture * texture, SDL_Rect img_rect, float x, float y, bool flip_v, bool flip_h) {
    SDL_Rect src;

    src.x = img_rect.x;
    src.y = img_rect.y;

    src.w = img_rect.w;
    src.h = img_rect.h;

    SDL_Rect dst;
    dst.x = x * RENDER_SCALE;
    dst.y = y * RENDER_SCALE;

    dst.w = src.w * RENDER_SCALE;
    dst.h = src.h * RENDER_SCALE;

    SDL_RendererFlip flip;

    if (flip_v) {
        flip = SDL_FLIP_VERTICAL;
    } else if (flip_h){
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
    
    SDL_RenderCopyEx(renderer->sdl_renderer, texture, &src, &dst, 0, NULL, flip);
}

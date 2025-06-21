#pragma once

#define MAX_ENTITY_COUNT 255 * 255

typedef struct Constants {
    int screen_width; 
    int screen_height; 
    float render_scale; 
    float display_width; 
    float display_height; 
    int refresh_rate;
    float time_step;
} Constants;

extern Constants * constants;

// not really constant but who cares
#define SCREEN_WIDTH (constants->screen_width)
#define SCREEN_HEIGHT (constants->screen_height)
#define RENDER_SCALE (constants->render_scale)
#define DISPLAY_WIDTH (constants->display_width)
#define DISPLAY_HEIGHT (constants->display_height)
#define REFRESH_RATE (constants->refresh_rate)
#define TIME_STEP (constants->time_step)


void init_constants();

void update_scale();

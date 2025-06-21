#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

Constants * constants;


void init_constants() {
    constants = malloc(sizeof(Constants));

    constants->screen_width = 1920;
    constants->screen_height = 1080;
    constants->display_width = 480;
    constants->display_height = 270;
        
    float scale_x = constants->screen_width / constants->display_width;
    float scale_y = constants->screen_height/ constants->display_height;
    constants->render_scale = (scale_x > scale_y) ? scale_y : scale_x;

    constants->refresh_rate= 165;
    constants->time_step = 0.01f;
}

void update_scale() {
    printf("updateing!\n");
    float scale_x = constants->screen_width / constants->display_width;
    float scale_y = constants->screen_height/ constants->display_height;
    constants->render_scale = (int) (scale_x > scale_y) ? scale_y : scale_x;
}

#include "../renderer/renderer.h"
#include "../renderer/drawing_context.h"
#include <stdbool.h>
#include <math.h>

// Note: this is a completly passive struct and should not actively 
// do anything. If it does, my code sucks 

typedef struct Hud {
    int health;
    int max_health;

    int power;
    int max_power;

    int score;

    bool is_start;
    bool is_game_over;

} Hud;

void hud_init(Hud * hud);

void hud_update(Hud * hud, DrawingContext * drawing_context);

void hud_draw(Hud * hud, DrawingContext * drawing_context);

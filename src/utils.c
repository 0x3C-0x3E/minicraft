#include "utils.h"

bool rects_collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {

    if (x1 + w1 <= x2 || x2 + w2 <= x1)
        return false;

    if (y1 + h1 <= y2 || y2 + h2 <= y1)
        return false;

    return true;
}



unsigned int seed_from_urandom() {
    unsigned int seed = 0;
    FILE *urandom = fopen("/dev/urandom", "rb");
    if (urandom) {
        fread(&seed, sizeof(seed), 1, urandom);
        fclose(urandom);
    } else {
        // Fallback if /dev/urandom isn't available
        seed = (unsigned int)time(NULL);
    }
    return seed;
}

void init_rand() {
#if defined(_WIN32) || defined(_WIN64)
    printf("RANDOM FUNCTION FOR WINDOWS NOT DEFINED! (i was lazy)\n");
#else
    unsigned int seed = seed_from_urandom();
#endif
    srand(seed);
}

int get_random(int min, int max) {
    if (max < min) {
        return -1;
    }
    init_rand();

    return rand() % (max - min + 1 ) + min;
}

#pragma once
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

bool rects_collide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);


// Note: min is inclusive, while max is exclusive; like it should be!
int get_random(int min, int max);


#include <fcntl.h>
#include <unistd.h>

unsigned int seed_from_urandom();


void init_rand();

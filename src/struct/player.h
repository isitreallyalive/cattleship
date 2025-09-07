#pragma once
#include "ship.h"
#include "vec.h"

typedef struct player {
    ships_t ships;
    vec_t cur;
} player_t;

player_t player_init();
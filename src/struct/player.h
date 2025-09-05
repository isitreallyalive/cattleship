#pragma once
#include "board.h"
#include "vec.h"

typedef struct player {
    board_t shots;
    vec_t cur;
} player_t;

player_t player_init();
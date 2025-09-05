#include "player.h"
#include <string.h>

player_t player_init() {
  player_t p;
  memset(&p.shots, false, sizeof(board_t)); // init board
  p.cur = VEC_ZERO;                         // init cursor
  return p;
}
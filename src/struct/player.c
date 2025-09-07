#include "player.h"
#include "ship.h"
#include <string.h>

player_t player_init() {
  player_t p;
  for (int s = 0; s < SHIP_COUNT; ++s) {
    ship_place(&p.ships, s); // init ships
  }
  p.cur = VEC_ZERO; // init cursor
  return p;
}
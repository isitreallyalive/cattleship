#include "ship.h"
#include "const.h"
#include <stdlib.h>

const int SHIP_SIZES[SHIP_COUNT] = {[SHIP_CARRIER] = 5,
                                    [SHIP_BATTLESHIP] = 4,
                                    [SHIP_CRUISER] = 3,
                                    [SHIP_SUBMARINE] = 3,
                                    [SHIP_DESTROYER] = 2};

const char *SHIP_NAMES[SHIP_COUNT] = {[SHIP_CARRIER] = "Carrier",
                                      [SHIP_BATTLESHIP] = "Battleship",
                                      [SHIP_CRUISER] = "Cruiser",
                                      [SHIP_SUBMARINE] = "Submarine",
                                      [SHIP_DESTROYER] = "Destroyer"};

// returns (x, y) for the i-th segment of a ship at pos with rotation rot
static vec_t ship_segment(const vec_t pos, const rotation_t rot, const int i) {
  vec_t segment = pos;
  switch (rot) {
  case ROT_0:
    segment.x += i;
    break;
  case ROT_90:
    segment.y += i;
    break;
  case ROT_180:
    segment.x -= i;
    break;
  case ROT_270:
    segment.y -= i;
    break;
  }
  return segment;
}

// checks if a ship at pos with rot and size would overlap any other ship
static bool overlaps(const ships_t *ships, const ship_type_t skip,
                     const vec_t pos, const rotation_t rot, const int size) {
  for (int s = 0; s < SHIP_COUNT; ++s) {
    if (s == skip)
      continue; // skip the ship being placed
    const ship_t *other = &(*ships)[s];
    if (other->type < 0 || other->type >= SHIP_COUNT)
      continue; // skip unplaced ships
    int osize = SHIP_SIZES[other->type];
    for (int i = 0; i < size; ++i) {
      vec_t seg = ship_segment(pos, rot, i);
      for (int j = 0; j < osize; ++j) {
        vec_t oseg = ship_segment(other->pos, other->rot, j);
        if (vec_eq(&seg, &oseg))
          return true;
      }
    }
  }
  return false;
}

// check if a ship at pos with rot and size fits on the board
static bool fits_on_board(const vec_t pos, const rotation_t rot,
                          const int size) {
  for (int i = 0; i < size; ++i) {
    vec_t seg = ship_segment(pos, rot, i);
    if (seg.x < 0 || seg.x >= BOARD_SIZE || seg.y < 0 || seg.y >= BOARD_SIZE) {
      return false;
    }
  }
  return true;
}

void ship_place(ships_t *ships, const ship_type_t type) {
  int size = SHIP_SIZES[type];
  rotation_t rot;
  vec_t pos;

  // try random positions and rotations
  do {
    rot = (rotation_t)(rand() % 4);
    pos.x = rand() % BOARD_SIZE;
    pos.y = rand() % BOARD_SIZE;
  } while (overlaps(ships, type, pos, rot, size) ||
           !fits_on_board(pos, rot, size));

  // place the ship with the chosen position and rotation
  ship_t *ship = &(*ships)[type];
  ship->type = type;
  ship->rot = rot;
  ship->pos = pos;
  for (int i = 0; i < MAX_SHIP_SIZE; ++i) {
    ship->hits[i] = false;
  }
}
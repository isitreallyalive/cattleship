#pragma once
#include "vec.h"
#include <stdbool.h>

#define SHIP_COUNT 5
#define MAX_SHIP_SIZE 5

extern const int SHIP_SIZES[SHIP_COUNT];
extern const char *SHIP_NAMES[SHIP_COUNT];

typedef enum ship_type {
    SHIP_CARRIER,
    SHIP_BATTLESHIP,
    SHIP_CRUISER,
    SHIP_SUBMARINE,
    SHIP_DESTROYER
} ship_type_t;

typedef enum rotation { ROT_0, ROT_90, ROT_180, ROT_270 } rotation_t;

typedef struct ship {
    ship_type_t type;
    rotation_t rot;
    vec_t pos;
    bool hits[MAX_SHIP_SIZE];
} ship_t;

typedef ship_t ships_t[SHIP_COUNT];

/**
 * Randomly place a ship of the given type in the provided ships array.
 * 
 * @param ships Pointer to the ships array to modify.
 * @param type The type of ship to place.
 */
void ship_place(ships_t *ships, const ship_type_t type);
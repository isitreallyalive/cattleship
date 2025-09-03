#pragma once
#include <stdbool.h>

typedef struct pos
{
    int x;
    int y;
} pos_t;

/**
 * Create a new position from a coordinate pair.
 *
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @returns A position representing those coordinates.
 */
pos_t pos_init(int x, int y);

/**
 * Check if two positions are equal.
 *
 * @param p1 First position.
 * @param p2 Second position.
 * @returns TRUE if the positions are equal, FALSE otherwise.
 */
bool pos_eq(const pos_t *p1, const pos_t *p2);
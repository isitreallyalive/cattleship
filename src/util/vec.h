#pragma once
#include <stdbool.h>

typedef struct vec
{
    int x;
    int y;
} vec_t;

/**
 * Create a new vector from the provided components.
 *
 * @param x The x component.
 * @param y The y component.
 * @returns The vector corresponding to the provided components.
 */
vec_t vec_init(const int x, const int y);

/**
 * Add the provided scalars to the components of the vector,
 * but do not allow the result to go out of the bounds of the board.
 *
 * @param p Pointer to the vector to modify.
 * @param dx Change in x.
 * @param dy Change in y.
 */
void vec_add(vec_t *p, const int dx, const int dy);

/**
 * Check if two vectors are equal.
 *
 * @param p1 First position.
 * @param p2 Second position.
 * @returns TRUE if the vectors are equal, FALSE otherwise.
 */
bool vec_eq(const vec_t *p1, const vec_t *p2);
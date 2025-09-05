#pragma once
#include <stdbool.h>

typedef struct vec
{
    int x;
    int y;
} vec_t;

#define VEC(x, y) ((vec_t){(x), (y)})
extern const vec_t VEC_ZERO;

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
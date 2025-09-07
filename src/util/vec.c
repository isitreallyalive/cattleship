#include "vec.h"

const vec_t VEC_ZERO = VEC(0, 0);

bool vec_eq(const vec_t *p1, const vec_t *p2) {
  return p1->x == p2->x && p1->y == p2->y;
}
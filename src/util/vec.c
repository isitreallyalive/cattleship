#include "vec.h"
#include "../game.h";

static inline int clamp(int val, int min, int max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

vec_t vec_init(const int x, const int y)
{
    return (vec_t){x, y};
}

void vec_add(vec_t *p, const int dx, const int dy)
{
    p->x = clamp(p->x + dx, 0, CELL_COUNT - 1);
    p->y = clamp(p->y + dy, 0, CELL_COUNT - 1);
}

bool vec_eq(const vec_t *p1, const vec_t *p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}
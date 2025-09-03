#include "pos.h"

pos_t pos_init(int x, int y) {
    return (pos_t){ x, y };
}

bool pos_eq(const pos_t *p1, const pos_t *p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}
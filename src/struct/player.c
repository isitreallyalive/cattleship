#include "player.h"
#include <string.h>

player_t player_init() {
	player_t p;
	memset(&p.shots, false, sizeof(board_t)); // init board
	p.cur = vec_init(0, 0); // init cursor
	return p;
}
#ifndef TERMINAL_PURSUIT_MOVEMENT_H
#define TERMINAL_PURSUIT_MOVEMENT_H

#include "terminal_pursuit/game.h"

/** Outcome of interpreting one byte of player input. */
typedef enum {
    PLAYER_INPUT_IGNORED,
    PLAYER_TURN_ACCEPTED,
    PLAYER_REQUESTED_QUIT
} PlayerInputResult;

/**
 * Applies W/A/S/D movement without crossing the border. A directional key
 * consumes a turn even when the player is already against a wall.
 */
PlayerInputResult movement_apply_player_input(GameState *state, int input);

/**
 * Advances the pursuer. Adjacent cells trigger a direct chase; otherwise the
 * supplied direction (0-7) selects one of eight neighboring cells.
 */
void movement_advance_pursuer(GameState *state, int random_direction);

#endif


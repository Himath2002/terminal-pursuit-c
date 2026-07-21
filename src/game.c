#include "terminal_pursuit/game.h"

#include <stddef.h>

bool game_initialize(GameState *state, int rows, int columns)
{
    if (state == NULL
            || rows < TP_MIN_DIMENSION
            || rows > TP_MAX_ROWS
            || columns < TP_MIN_DIMENSION
            || columns > TP_MAX_COLUMNS) {
        return false;
    }

    state->rows = rows;
    state->columns = columns;
    state->player = (Position){1, 1};
    state->pursuer = (Position){rows, columns};
    state->target = (Position){0, 0};
    state->status = GAME_RUNNING;
    return true;
}

bool game_is_playable_position(const GameState *state, Position position)
{
    return state != NULL
            && position.row >= 1
            && position.row <= state->rows
            && position.column >= 1
            && position.column <= state->columns;
}

bool game_positions_equal(Position first, Position second)
{
    return first.row == second.row && first.column == second.column;
}

bool game_place_target(GameState *state, Position candidate)
{
    if (!game_is_playable_position(state, candidate)
            || game_positions_equal(candidate, state->player)
            || game_positions_equal(candidate, state->pursuer)) {
        return false;
    }

    state->target = candidate;
    return true;
}

void game_update_status(GameState *state)
{
    if (state == NULL || state->status != GAME_RUNNING) {
        return;
    }

    if (game_positions_equal(state->player, state->pursuer)) {
        state->status = GAME_PLAYER_CAUGHT;
    } else if (game_positions_equal(state->player, state->target)) {
        state->status = GAME_PLAYER_WON;
    }
}

const char *game_status_message(GameStatus status)
{
    switch (status) {
        case GAME_PLAYER_WON:
            return "Target secured. You escaped the pursuit.";
        case GAME_PLAYER_CAUGHT:
            return "The pursuer reached your cell. Run complete.";
        case GAME_QUIT:
            return "Session ended by player.";
        case GAME_RUNNING:
        default:
            return "Pursuit in progress.";
    }
}


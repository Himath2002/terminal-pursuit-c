#include "terminal_pursuit/movement.h"

#include <ctype.h>
#include <stdlib.h>

static int step_toward(int difference)
{
    if (difference > 0) {
        return -1;
    }
    if (difference < 0) {
        return 1;
    }
    return 0;
}

PlayerInputResult movement_apply_player_input(GameState *state, int input)
{
    Position candidate;
    int normalized_input;

    if (state == NULL || state->status != GAME_RUNNING) {
        return PLAYER_INPUT_IGNORED;
    }

    normalized_input = tolower((unsigned char)input);
    if (normalized_input == 'q') {
        state->status = GAME_QUIT;
        return PLAYER_REQUESTED_QUIT;
    }

    candidate = state->player;
    switch (normalized_input) {
        case 'w':
            candidate.row--;
            break;
        case 's':
            candidate.row++;
            break;
        case 'a':
            candidate.column--;
            break;
        case 'd':
            candidate.column++;
            break;
        default:
            return PLAYER_INPUT_IGNORED;
    }

    if (game_is_playable_position(state, candidate)) {
        state->player = candidate;
    }
    return PLAYER_TURN_ACCEPTED;
}

void movement_advance_pursuer(GameState *state, int random_direction)
{
    static const Position direction_delta[8] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };
    Position candidate;
    int row_difference;
    int column_difference;

    if (state == NULL || state->status != GAME_RUNNING) {
        return;
    }

    row_difference = state->pursuer.row - state->player.row;
    column_difference = state->pursuer.column - state->player.column;
    candidate = state->pursuer;

    if (abs(row_difference) <= 1 && abs(column_difference) <= 1) {
        candidate.row += step_toward(row_difference);
        candidate.column += step_toward(column_difference);
    } else if (random_direction >= 0 && random_direction < 8) {
        candidate.row += direction_delta[random_direction].row;
        candidate.column += direction_delta[random_direction].column;
    }

    if (game_is_playable_position(state, candidate)
            && !game_positions_equal(candidate, state->target)) {
        state->pursuer = candidate;
    }
}


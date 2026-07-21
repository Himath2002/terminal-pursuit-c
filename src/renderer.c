#include "terminal_pursuit/renderer.h"

#include <stdio.h>

static char cell_symbol(const GameState *state, Position cell)
{
    if (cell.row == 0
            || cell.row == state->rows + 1
            || cell.column == 0
            || cell.column == state->columns + 1) {
        return '#';
    }
    if (game_positions_equal(cell, state->player)
            && game_positions_equal(cell, state->pursuer)) {
        return 'X';
    }
    if (game_positions_equal(cell, state->player)) {
        return 'P';
    }
    if (game_positions_equal(cell, state->pursuer)) {
        return '~';
    }
    if (game_positions_equal(cell, state->target)) {
        return '@';
    }
    return ' ';
}

void renderer_draw(const GameState *state)
{
    int row;
    int column;

    if (state == NULL) {
        return;
    }

    printf("\033[2J\033[H");
    printf("TERMINAL PURSUIT  |  W/A/S/D move  |  Q quit\n\n");

    for (row = 0; row <= state->rows + 1; row++) {
        for (column = 0; column <= state->columns + 1; column++) {
            Position cell = {row, column};
            putchar(cell_symbol(state, cell));
        }
        putchar('\n');
    }

    printf("\nP you   ~ pursuer   @ target   # boundary");
    if (state->status != GAME_RUNNING) {
        printf("\n\n%s", game_status_message(state->status));
    }
    printf("\n");
    fflush(stdout);
}


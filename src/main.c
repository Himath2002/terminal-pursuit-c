#include "terminal_pursuit/game.h"
#include "terminal_pursuit/movement.h"
#include "terminal_pursuit/random_source.h"
#include "terminal_pursuit/renderer.h"
#include "terminal_pursuit/terminal.h"

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage(const char *program_name)
{
    printf("Usage: %s <rows> <columns>\n", program_name);
    printf("       %s --help\n\n", program_name);
    printf("Rows:    %d-%d\n", TP_MIN_DIMENSION, TP_MAX_ROWS);
    printf("Columns: %d-%d\n", TP_MIN_DIMENSION, TP_MAX_COLUMNS);
}

static bool parse_dimension(const char *text, int maximum, int *value)
{
    char *end;
    long parsed;

    if (text == NULL || value == NULL) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtol(text, &end, 10);
    if (errno != 0
            || end == text
            || *end != '\0'
            || parsed < TP_MIN_DIMENSION
            || parsed > maximum
            || parsed > INT_MAX) {
        return false;
    }

    *value = (int)parsed;
    return true;
}

static void place_random_target(GameState *state)
{
    Position candidate;

    do {
        candidate.row = random_source_between(1, state->rows);
        candidate.column = random_source_between(1, state->columns);
    } while (!game_place_target(state, candidate));
}

int main(int argc, char *argv[])
{
    GameState state;
    int rows;
    int columns;

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return EXIT_SUCCESS;
    }
    if (argc != 3
            || !parse_dimension(argv[1], TP_MAX_ROWS, &rows)
            || !parse_dimension(argv[2], TP_MAX_COLUMNS, &columns)) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    if (!game_initialize(&state, rows, columns)) {
        fputs("Unable to initialize the requested board.\n", stderr);
        return EXIT_FAILURE;
    }

    random_source_seed();
    place_random_target(&state);

    while (state.status == GAME_RUNNING) {
        char key;
        PlayerInputResult input_result;

        renderer_draw(&state);
        if (!terminal_read_key(&key)) {
            state.status = GAME_QUIT;
            break;
        }

        input_result = movement_apply_player_input(&state, key);
        if (input_result == PLAYER_TURN_ACCEPTED) {
            movement_advance_pursuer(&state, random_source_between(0, 7));
            game_update_status(&state);
        }
    }

    renderer_draw(&state);
    return EXIT_SUCCESS;
}


#include "terminal_pursuit/game.h"
#include "terminal_pursuit/movement.h"

#include <stdio.h>
#include <stdlib.h>

static int failures;

#define EXPECT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            failures++; \
        } \
    } while (0)

static GameState new_state(void)
{
    GameState state;
    EXPECT_TRUE(game_initialize(&state, 8, 12));
    EXPECT_TRUE(game_place_target(&state, (Position){4, 6}));
    return state;
}

static void test_initial_state(void)
{
    GameState state = new_state();

    EXPECT_TRUE(state.status == GAME_RUNNING);
    EXPECT_TRUE(game_positions_equal(state.player, (Position){1, 1}));
    EXPECT_TRUE(game_positions_equal(state.pursuer, (Position){8, 12}));
    EXPECT_TRUE(game_is_playable_position(&state, (Position){8, 12}));
    EXPECT_TRUE(!game_is_playable_position(&state, (Position){0, 1}));
}

static void test_wall_move_consumes_turn(void)
{
    GameState state = new_state();
    PlayerInputResult result = movement_apply_player_input(&state, 'w');

    EXPECT_TRUE(result == PLAYER_TURN_ACCEPTED);
    EXPECT_TRUE(game_positions_equal(state.player, (Position){1, 1}));
}

static void test_adjacent_pursuer_chases_diagonally(void)
{
    GameState state = new_state();
    state.player = (Position){3, 3};
    state.pursuer = (Position){4, 4};

    movement_advance_pursuer(&state, 0);
    game_update_status(&state);

    EXPECT_TRUE(game_positions_equal(state.pursuer, state.player));
    EXPECT_TRUE(state.status == GAME_PLAYER_CAUGHT);
}

static void test_pursuer_does_not_enter_target_cell(void)
{
    GameState state = new_state();
    state.pursuer = (Position){5, 6};
    state.player = (Position){1, 1};

    movement_advance_pursuer(&state, 0);

    EXPECT_TRUE(game_positions_equal(state.pursuer, (Position){5, 6}));
}

static void test_player_reaches_target(void)
{
    GameState state = new_state();
    state.player = (Position){4, 5};
    state.pursuer = (Position){8, 12};

    EXPECT_TRUE(movement_apply_player_input(&state, 'd') == PLAYER_TURN_ACCEPTED);
    game_update_status(&state);

    EXPECT_TRUE(state.status == GAME_PLAYER_WON);
}

int main(void)
{
    test_initial_state();
    test_wall_move_consumes_turn();
    test_adjacent_pursuer_chases_diagonally();
    test_pursuer_does_not_enter_target_cell();
    test_player_reaches_target();

    if (failures != 0) {
        fprintf(stderr, "%d test expectation(s) failed.\n", failures);
        return EXIT_FAILURE;
    }

    puts("All Terminal Pursuit checks passed.");
    return EXIT_SUCCESS;
}


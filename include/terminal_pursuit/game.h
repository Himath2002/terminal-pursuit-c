#ifndef TERMINAL_PURSUIT_GAME_H
#define TERMINAL_PURSUIT_GAME_H

#include <stdbool.h>

#define TP_MIN_DIMENSION 5
#define TP_MAX_ROWS 60
#define TP_MAX_COLUMNS 160

/** A row and column inside the playable area. */
typedef struct {
    int row;
    int column;
} Position;

/** The terminal states of a pursuit session. */
typedef enum {
    GAME_RUNNING,
    GAME_PLAYER_WON,
    GAME_PLAYER_CAUGHT,
    GAME_QUIT
} GameStatus;

/**
 * Complete game state. Rows and columns describe the playable area; the
 * renderer adds a one-cell border around it.
 */
typedef struct {
    int rows;
    int columns;
    Position player;
    Position pursuer;
    Position target;
    GameStatus status;
} GameState;

/** Initializes a session with opposing corner positions. */
bool game_initialize(GameState *state, int rows, int columns);

/** Returns whether a position is inside the playable area. */
bool game_is_playable_position(const GameState *state, Position position);

/** Returns whether two positions refer to the same cell. */
bool game_positions_equal(Position first, Position second);

/**
 * Places the target when the candidate is playable and does not overlap an
 * actor. Returns false when another candidate is required.
 */
bool game_place_target(GameState *state, Position candidate);

/** Resolves collision and victory conditions, with capture taking precedence. */
void game_update_status(GameState *state);

/** Returns the final message associated with the current status. */
const char *game_status_message(GameStatus status);

#endif


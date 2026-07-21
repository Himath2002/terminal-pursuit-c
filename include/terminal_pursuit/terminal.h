#ifndef TERMINAL_PURSUIT_TERMINAL_H
#define TERMINAL_PURSUIT_TERMINAL_H

#include <stdbool.h>

/**
 * Reads one byte immediately from a terminal, restoring the original terminal
 * settings before returning. Piped input is supported for smoke tests.
 */
bool terminal_read_key(char *key);

#endif


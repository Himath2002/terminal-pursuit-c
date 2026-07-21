#ifndef TERMINAL_PURSUIT_RANDOM_SOURCE_H
#define TERMINAL_PURSUIT_RANDOM_SOURCE_H

/** Seeds the process-wide pseudo-random source from wall-clock time. */
void random_source_seed(void);

/** Returns an integer in the inclusive range [low, high]. */
int random_source_between(int low, int high);

#endif


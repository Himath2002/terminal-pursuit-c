# Contributing

Terminal Pursuit is intentionally compact. Changes should strengthen the core
terminal experience without turning the project into a framework.

## Workflow

1. Create a focused branch from main.
2. Keep game rules independent of terminal rendering and input.
3. Run make clean all check.
4. Use a concise imperative commit message.
5. Open a pull request that explains behavior changes and verification.

All C code must compile as C11 with strict compiler warnings enabled.

# Changelog

Notable changes to Terminal Pursuit are recorded here. The project follows
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0] - 2026-07-21

### Added

- Configurable turn-based terminal pursuit for POSIX systems.
- Explicit game state and independent input, movement, rules, random, and
  rendering modules.
- Immediate W/A/S/D input with terminal restoration and clean Q exit.
- Strict C11 build with warnings treated as errors.
- Focused movement and outcome checks.
- Ubuntu and macOS continuous integration.
- Monthly GitHub Actions dependency review.
- Project-specific architecture and terminal visuals.

### Changed

- Replaced the earlier dynamic character grid with derived rendering from
  constant-size state.
- Reimplemented terminal and random utilities behind narrow interfaces.
- Added robust numeric parsing and practical board limits.

[Unreleased]: https://github.com/Himath2002/terminal-pursuit-c/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/Himath2002/terminal-pursuit-c/releases/tag/v1.0.0

CC ?= cc

TARGET := build/terminal-pursuit
TEST_TARGET := build/test-game
INCLUDE_DIR := include
OBJECT_DIR := build/obj

STANDARD_FLAGS := -std=c11
WARNING_FLAGS := -Wall -Wextra -Wpedantic -Werror
OPTIMIZATION_FLAGS ?= -O2
CPPFLAGS += -I$(INCLUDE_DIR)
CFLAGS += $(STANDARD_FLAGS) $(WARNING_FLAGS) $(OPTIMIZATION_FLAGS)

CORE_SOURCES := src/game.c src/movement.c
APP_SOURCES := $(CORE_SOURCES) src/main.c src/random_source.c src/renderer.c src/terminal.c
APP_OBJECTS := $(APP_SOURCES:src/%.c=$(OBJECT_DIR)/%.o)
TEST_OBJECTS := $(OBJECT_DIR)/test_game.o $(CORE_SOURCES:src/%.c=$(OBJECT_DIR)/%.o)
DEPENDENCIES := $(APP_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all check clean debug run

all: $(TARGET)

$(TARGET): $(APP_OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJECT_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJECT_DIR)/test_game.o: tests/test_game.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

check: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET) 12 28

debug: OPTIMIZATION_FLAGS := -O0 -g3
debug: clean all

clean:
	rm -rf build

-include $(DEPENDENCIES)


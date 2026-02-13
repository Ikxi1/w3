# Makefile for w3 tests
# Requires MinGW or similar Windows C compiler

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include -I.
LDFLAGS = -L. -luser32 -lgdi32

# Unity framework files
UNITY_SRC = unity/unity.c
UNITY_OBJ = unity/unity.o

# Source files to test
SRC_DIR = ../src
MONITOR_SRC = $(SRC_DIR)/monitor.c
MONITOR_OBJ = monitor.o

# Test executables
TEST_MAIN = test_main.exe
TEST_MONITOR = test_monitor.exe
TEST_KEYBOARD = test_keyboard.exe
TEST_SHORTCUTS = test_shortcuts.exe
TEST_DESKTOP = test_desktop.exe
TEST_INTEGRATION = test_integration.exe

# All test executables
TESTS = $(TEST_MAIN) $(TEST_MONITOR) $(TEST_KEYBOARD) $(TEST_SHORTCUTS) $(TEST_DESKTOP) $(TEST_INTEGRATION)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m # No Color

.PHONY: all clean run test help

all: $(TESTS)

# Build Unity framework
$(UNITY_OBJ): $(UNITY_SRC)
	$(CC) $(CFLAGS) -c $(UNITY_SRC) -o $(UNITY_OBJ)

# Build monitor.o from source for testing
$(MONITOR_OBJ): $(MONITOR_SRC)
	$(CC) $(CFLAGS) -D_DEBUG -c $(MONITOR_SRC) -o $(MONITOR_OBJ)

# Build test executables
$(TEST_MAIN): test_main.c $(UNITY_OBJ)
	$(CC) $(CFLAGS) test_main.c $(UNITY_OBJ) -o $(TEST_MAIN) $(LDFLAGS)

$(TEST_MONITOR): test_monitor.c $(UNITY_OBJ) $(MONITOR_OBJ)
	$(CC) $(CFLAGS) test_monitor.c $(MONITOR_OBJ) $(UNITY_OBJ) -o $(TEST_MONITOR) $(LDFLAGS)

$(TEST_KEYBOARD): test_keyboard.c $(UNITY_OBJ)
	$(CC) $(CFLAGS) test_keyboard.c $(UNITY_OBJ) -o $(TEST_KEYBOARD) $(LDFLAGS)

$(TEST_SHORTCUTS): test_shortcuts.c $(UNITY_OBJ)
	$(CC) $(CFLAGS) test_shortcuts.c $(UNITY_OBJ) -o $(TEST_SHORTCUTS) $(LDFLAGS)

$(TEST_DESKTOP): test_desktop.c $(UNITY_OBJ)
	$(CC) $(CFLAGS) test_desktop.c $(UNITY_OBJ) -o $(TEST_DESKTOP) $(LDFLAGS)

$(TEST_INTEGRATION): test_integration.c $(UNITY_OBJ)
	$(CC) $(CFLAGS) test_integration.c $(UNITY_OBJ) -o $(TEST_INTEGRATION) $(LDFLAGS)

# Run all tests
test: all
	@echo "Running all tests..."
	@echo "===================="
	@for test in $(TESTS); do \
		echo ""; \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo ""
	@echo "===================="
	@echo "All tests passed!"

# Run individual tests
run-main: $(TEST_MAIN)
	./$(TEST_MAIN)

run-monitor: $(TEST_MONITOR)
	./$(TEST_MONITOR)

run-keyboard: $(TEST_KEYBOARD)
	./$(TEST_KEYBOARD)

run-shortcuts: $(TEST_SHORTCUTS)
	./$(TEST_SHORTCUTS)

run-desktop: $(TEST_DESKTOP)
	./$(TEST_DESKTOP)

run-integration: $(TEST_INTEGRATION)
	./$(TEST_INTEGRATION)

# Clean build artifacts
clean:
	rm -f $(TESTS) $(UNITY_OBJ) $(MONITOR_OBJ)
	rm -f *.o

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build all tests"
	@echo "  test         - Build and run all tests"
	@echo "  run-main     - Run main utility tests"
	@echo "  run-monitor  - Run monitor tests"
	@echo "  run-keyboard - Run keyboard tests"
	@echo "  run-shortcuts - Run shortcuts tests"
	@echo "  run-desktop  - Run desktop tests"
	@echo "  run-integration - Run integration tests"
	@echo "  clean        - Remove build artifacts"
	@echo "  help         - Show this help message"

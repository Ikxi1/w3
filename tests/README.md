# W3 Test Suite

This directory contains comprehensive unit tests for the w3 Windows utility project.

## Test Framework

The tests use the [Unity](https://github.com/ThrowTheSwitch/Unity) testing framework, a lightweight and widely-used C testing framework perfect for embedded and systems programming.

## Test Coverage

### test_main.c
Tests for main utility functions and data structures:
- Vec2 structure initialization and operations
- Arithmetic operations on Vec2 (addition, subtraction, midpoint)
- Distance calculations (Manhattan and Euclidean)
- Bounds checking
- Screen coordinate handling
- Window style flags
- Error message handling

### test_monitor.c
Tests for monitor management functionality:
- MonitorInfo structure initialization and assignment
- Monitor comparison function (compare_monitors)
- Monitor name sorting
- Vec2 coordinate structures
- Edge cases (empty names, equal names)

### test_keyboard.c
Tests for keyboard event handling:
- KbdEvent structure initialization
- Keydown/keyup event handling
- Keyboard state management (shift, ctrl, macro mode)
- Virtual key code constants
- Custom WM_KBD_EVENT message
- Flag handling (LLKHF_INJECTED)
- Number keys and arrow keys

### test_shortcuts.c
Tests for shortcut key combinations:
- INPUT structure initialization
- Key combination sequences (Win+Shift+S, Win+I, Alt+F4)
- Keydown and keyup flags
- Virtual key constants
- Input array size calculations
- Shortcut patterns for:
  - Screenshot (Win+Shift+S)
  - Settings (Win+I)
  - Start menu (Win)
  - Close program (Alt+F4)

### test_desktop.c
Tests for window enumeration functionality:
- AppList structure initialization
- Window handle management
- Memory allocation patterns
- Window visibility logic
- Enum callback return values
- LPARAM casting patterns

## Building and Running Tests

### Prerequisites

- MinGW-w64 or similar Windows C compiler with GCC
- Windows SDK (for Windows.h and WinAPI)
- Make utility

### Build All Tests

```bash
cd tests
make all
```

### Run All Tests

```bash
make test
```

### Run Individual Test Suites

```bash
make run-main       # Run main utility tests
make run-monitor    # Run monitor tests
make run-keyboard   # Run keyboard tests
make run-shortcuts  # Run shortcuts tests
make run-desktop    # Run desktop tests
```

### Clean Build Artifacts

```bash
make clean
```

## Test Output

When all tests pass, you'll see output like:

```
test_main.exe
--------------------
13 Tests 0 Failures 0 Ignored
OK

test_monitor.exe
--------------------
8 Tests 0 Failures 0 Ignored
OK

test_keyboard.exe
--------------------
9 Tests 0 Failures 0 Ignored
OK

test_shortcuts.exe
--------------------
10 Tests 0 Failures 0 Ignored
OK

test_desktop.exe
--------------------
10 Tests 0 Failures 0 Ignored
OK

====================
All tests passed!
```

## Notes on Test Limitations

This project heavily relies on Windows API and hardware interactions (keyboard hooks, cursor positioning, window management). Many functions are difficult to unit test without mocking the entire Windows API or running in a full Windows environment.

The tests focus on:
1. **Data structures**: Verifying that structures are correctly defined and can hold expected values
2. **Pure logic**: Testing functions that don't depend on external state
3. **Constants**: Verifying that constants and flags are correctly defined
4. **Patterns**: Testing common patterns used throughout the codebase

Functions that directly interact with Windows API (like `get_monitors()`, `SetCursorPos()`, keyboard hooks, etc.) are not directly tested but their data structures and logic patterns are thoroughly validated.

## Adding New Tests

To add new tests:

1. Create a new test file `test_<module>.c` in the `tests` directory
2. Include Unity headers: `#include "unity/unity.h"`
3. Implement test functions with the naming convention `test_<functionality>()`
4. Add `setUp()` and `tearDown()` functions
5. Create a `main()` function that calls `UNITY_BEGIN()`, `RUN_TEST()` for each test, and `UNITY_END()`
6. Update the Makefile to build and run your new test

Example test structure:

```c
#include "unity/unity.h"

void setUp(void) {
    // Setup code before each test
}

void tearDown(void) {
    // Cleanup code after each test
}

void test_my_function(void) {
    TEST_ASSERT_EQUAL_INT(2, 1 + 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_my_function);
    return UNITY_END();
}
```

## Continuous Integration

These tests can be integrated into a CI/CD pipeline. The Makefile returns appropriate exit codes:
- 0: All tests passed
- Non-zero: One or more tests failed

## License

Tests are part of the w3 project and follow the same license.

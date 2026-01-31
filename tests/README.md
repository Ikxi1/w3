# W3 Test Suite

This directory contains comprehensive unit tests for the w3 Windows utility project.

## Test Framework

The tests use the [Unity](https://github.com/ThrowTheSwitch/Unity) testing framework, a lightweight and widely-used C testing framework perfect for embedded and systems programming.

## Test Coverage

### test_main.c
Tests for main utility functions (5 tests):
- Vec2 arithmetic operations (addition, subtraction)
- Distance calculations (Manhattan and Euclidean)
- Midpoint calculation
- Bounds checking
- Error message null checking

### test_monitor.c
Tests for monitor management functionality (6 tests):
- Monitor comparison function (equal, less than, greater than)
- Edge cases (empty names, one empty)
- MonitorInfo structure assignment

### test_keyboard.c
Tests for keyboard event handling (2 tests):
- Various key assignments (letters, arrows)
- Custom WM_KBD_EVENT message

### test_shortcuts.c
Tests for shortcut key combinations (4 tests):
- Screenshot (Win+Shift+S)
- Settings (Win+I)
- Start menu (Win)
- Close program (Alt+F4)

### test_desktop.c
Tests for window enumeration functionality (3 tests):
- Memory allocation patterns
- Memory reallocation
- Window visibility logic

### test_integration.c
Integration tests demonstrating how components work together (11 tests):
- Screen number to array index conversions
- Key code to number/direction mappings
- Monitor center calculations
- Point-in-bounds checking
- Keyboard modifier combinations
- Multi-monitor array handling
- Keyboard event to shortcut mapping
- Monitor edge detection
- Screen switching validation
- Direction iteration patterns

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
make run-integration # Run integration tests
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
5 Tests 0 Failures 0 Ignored
OK

test_monitor.exe
--------------------
6 Tests 0 Failures 0 Ignored
OK

test_keyboard.exe
--------------------
2 Tests 0 Failures 0 Ignored
OK

test_shortcuts.exe
--------------------
4 Tests 0 Failures 0 Ignored
OK

test_desktop.exe
--------------------
3 Tests 0 Failures 0 Ignored
OK

test_integration.exe
--------------------
11 Tests 0 Failures 0 Ignored
OK

====================
All tests passed!
```

## Notes on Test Design

This test suite focuses on **meaningful logic** rather than basic language features.

### What We Test ✅

The tests focus on:
1. **Complex Logic**: Calculations, comparisons, and algorithms
2. **State Management**: How states change and interact
3. **Edge Cases**: Boundary conditions and error handling
4. **Integration Patterns**: How components work together

### What We Don't Test ❌

We intentionally avoid testing:
1. **Basic Initialization**: Structs zeroing to defaults (compiler's job)
2. **Simple Assignment**: Variable assignment (language feature)
3. **sizeof() Operations**: Structure sizes (not meaningful for logic)
4. **API Constants**: Windows virtual key codes (they never change)
5. **Trivial Boolean Logic**: TRUE/FALSE assignments

This approach keeps the test suite **lean, fast, and focused** on validating actual business logic rather than C language semantics.

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

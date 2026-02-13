# Testing Guide for w3 Project

## Overview

This document provides a comprehensive guide for testing the w3 Windows utility project. The test suite is designed to validate core functionality, data structures, and component interactions.

## Test Framework: Unity

The w3 project uses [Unity](https://github.com/ThrowTheSwitch/Unity), a lightweight C testing framework. Unity is:
- **Lightweight**: Minimal dependencies, easy to integrate
- **Portable**: Works across different platforms and compilers
- **Well-established**: Industry standard for embedded and systems C testing
- **Easy to use**: Simple assertion macros and test structure

## Test Suite Architecture

### Test Files

| Test File | Tests | Focus Area |
|-----------|-------|------------|
| `test_main.c` | 13 | Vec2 structure, utility functions, constants |
| `test_monitor.c` | 8 | MonitorInfo structure, comparison functions |
| `test_keyboard.c` | 9 | KbdEvent structure, state management |
| `test_shortcuts.c` | 10 | INPUT arrays, key combinations |
| `test_desktop.c` | 10 | Window enumeration, AppList structure |
| `test_integration.c` | 13 | Component interactions and patterns |

**Total: 63 unit tests**

## What's Tested vs. What's Not

### ✅ What IS Tested

1. **Data Structures**: All structs (Vec2, MonitorInfo, KbdEvent, AppList)
2. **Pure Logic**: Mathematical calculations, comparisons, conversions
3. **Constants**: Virtual key codes, window styles, message IDs
4. **Patterns**: Common coding patterns used throughout the codebase
5. **Integration Logic**: How components interact with each other

### ❌ What's NOT Tested

Due to Windows API dependencies, the following are NOT directly unit tested:

1. **Windows API Calls**: Functions like `SetCursorPos()`, `GetForegroundWindow()`
2. **Keyboard Hooks**: Low-level keyboard hook functionality
3. **Monitor Enumeration**: Actual monitor detection (requires hardware)
4. **Window Management**: Real window creation and manipulation
5. **Input Injection**: Actual keystroke injection via `SendInput()`

These components would require:
- Full Windows environment
- Mock frameworks for Windows API
- Integration/system tests rather than unit tests

## Building Tests

### Prerequisites

- **Compiler**: GCC (MinGW on Windows) or MSVC
- **Build Tool**: Make or CMake
- **Platform**: Windows (required for Windows.h)

### Using Make (Recommended for MinGW)

```bash
cd tests

# Build all tests
make all

# Run all tests
make test

# Run individual tests
make run-main
make run-monitor
make run-keyboard
make run-shortcuts
make run-desktop
make run-integration

# Clean build artifacts
make clean

# Show help
make help
```

### Using CMake (Cross-platform)

```bash
cd tests
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Run tests
ctest --output-on-failure

# Or run individually
./test_main
./test_monitor
# etc.
```

### Using Visual Studio

1. Open `tests/CMakeLists.txt` in Visual Studio
2. Build the test targets
3. Run tests from Test Explorer or command line

## Running Tests

### Batch Script (Windows)

```cmd
cd tests
run_tests.bat
```

### PowerShell Script (Windows)

```powershell
cd tests
.\run_tests.ps1
```

### Expected Output

When all tests pass:

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

test_integration.exe
--------------------
13 Tests 0 Failures 0 Ignored
OK

====================
All tests passed!
```

## Adding New Tests

### Step 1: Create Test File

Create a new file `test_<module>.c`:

```c
#include "unity/unity.h"
#include <Windows.h>

void setUp(void) {
    // Run before each test
}

void tearDown(void) {
    // Run after each test
}

void test_my_feature(void) {
    // Arrange
    int expected = 5;
    
    // Act
    int actual = 2 + 3;
    
    // Assert
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_my_feature);
    return UNITY_END();
}
```

### Step 2: Update Build Files

**Makefile:**
```makefile
TEST_NEW = test_new.exe
TESTS = ... $(TEST_NEW)

$(TEST_NEW): test_new.c $(UNITY_OBJ)
	$(CC) $(CFLAGS) test_new.c $(UNITY_OBJ) -o $(TEST_NEW) $(LDFLAGS)
```

**CMakeLists.txt:**
```cmake
add_executable(test_new test_new.c)
target_link_libraries(test_new unity ${WINDOWS_LIBS})
add_test(NAME test_new COMMAND test_new)
```

### Step 3: Run Your Test

```bash
make run-new  # or ./test_new
```

## Unity Assertion Macros

Common assertions used in the test suite:

```c
// Integers
TEST_ASSERT_EQUAL_INT(expected, actual)
TEST_ASSERT_EQUAL_UINT32(expected, actual)
TEST_ASSERT_GREATER_THAN(threshold, actual)
TEST_ASSERT_LESS_THAN(threshold, actual)

// Booleans
TEST_ASSERT_TRUE(condition)
TEST_ASSERT_FALSE(condition)
TEST_ASSERT_EQUAL(expected, actual)

// Pointers
TEST_ASSERT_NULL(pointer)
TEST_ASSERT_NOT_NULL(pointer)
TEST_ASSERT_EQUAL_PTR(expected, actual)

// Strings (wide strings)
TEST_ASSERT_EQUAL_STRING(expected, actual)

// Sizes
TEST_ASSERT_EQUAL_size_t(expected, actual)
```

See [Unity documentation](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md) for complete list.

## Test Design Principles

### 1. Arrange-Act-Assert Pattern

```c
void test_example(void) {
    // Arrange: Set up test data
    Vec2 v = {0};
    
    // Act: Execute the code under test
    v.x = 10;
    v.y = 20;
    
    // Assert: Verify the results
    TEST_ASSERT_EQUAL_INT(10, v.x);
    TEST_ASSERT_EQUAL_INT(20, v.y);
}
```

### 2. Test One Thing

Each test should verify one specific behavior:

```c
// Good: Tests one specific case
void test_vec2_addition(void) {
    Vec2 result;
    result.x = 10 + 20;
    result.y = 15 + 25;
    
    TEST_ASSERT_EQUAL_INT(30, result.x);
    TEST_ASSERT_EQUAL_INT(40, result.y);
}

// Avoid: Testing multiple unrelated things
void test_vec2_all_operations(void) {
    // Too much in one test
}
```

### 3. Descriptive Names

```c
// Good: Clear what's being tested
void test_monitor_comparison_equal_names(void)
void test_keyboard_event_keydown_assignment(void)

// Avoid: Vague names
void test1(void)
void test_stuff(void)
```

### 4. Test Edge Cases

```c
void test_monitor_comparison_with_empty_names(void)
void test_screen_switching_out_of_bounds(void)
void test_vec2_negative_values(void)
```

## Continuous Integration

The test suite is CI-ready:

```yaml
# Example GitHub Actions workflow
- name: Build and Test
  run: |
    cd tests
    make all
    make test
```

Exit codes:
- `0`: All tests passed
- Non-zero: One or more tests failed

## Troubleshooting

### Issue: Tests won't compile

**Solution**: Ensure you have Windows SDK installed for `Windows.h`

```bash
# Check if Windows.h is available
gcc -E -x c - -v < /dev/null 2>&1 | grep windows
```

### Issue: "make: command not found"

**Solution**: Install MinGW or add it to PATH

```bash
# Download from: https://www.mingw-w64.org/
# Or use package manager:
choco install mingw  # Windows with Chocolatey
```

### Issue: Unity files not found

**Solution**: Unity files should be in `tests/unity/`. Re-download if needed:

```bash
cd tests/unity
wget https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.c
wget https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.h
wget https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity_internals.h
```

## Future Enhancements

Potential additions to the test suite:

1. **Mock Framework**: Add mocking for Windows API calls
2. **Integration Tests**: Full system tests with real Windows environment
3. **Performance Tests**: Benchmark critical operations
4. **Coverage Reports**: Generate code coverage metrics
5. **Fuzzing**: Add fuzz testing for input validation

## Resources

- [Unity Testing Framework](https://github.com/ThrowTheSwitch/Unity)
- [Unity Assertions Reference](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md)
- [Test-Driven Development in C](https://www.embedded.com/test-driven-development-for-embedded-c/)

## Contributing Tests

When adding new functionality to w3:

1. Write tests first (TDD approach)
2. Ensure tests pass before committing
3. Run full test suite: `make test`
4. Update this documentation if adding new test patterns

## License

Tests are part of the w3 project and follow the same license.

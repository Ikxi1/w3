# Quick Test Reference

## Run All Tests
```bash
cd tests && make test
```

## Run Individual Test
```bash
make run-main          # Vec2, utilities
make run-monitor       # Monitor structures
make run-keyboard      # Keyboard events
make run-shortcuts     # Input combinations
make run-desktop       # Window enumeration
make run-integration   # Component interactions
```

## Common Assertions
```c
// Integers
TEST_ASSERT_EQUAL_INT(expected, actual)
TEST_ASSERT_GREATER_THAN(threshold, actual)
TEST_ASSERT_LESS_THAN(threshold, actual)

// Booleans
TEST_ASSERT_TRUE(condition)
TEST_ASSERT_FALSE(condition)

// Pointers
TEST_ASSERT_NULL(ptr)
TEST_ASSERT_NOT_NULL(ptr)

// Strings
TEST_ASSERT_EQUAL_STRING(expected, actual)
```

## Test Template
```c
#include "unity/unity.h"
#include <Windows.h>

void setUp(void) {}
void tearDown(void) {}

void test_my_feature(void) {
    // Arrange
    int value = 5;
    
    // Act
    int result = value * 2;
    
    // Assert
    TEST_ASSERT_EQUAL_INT(10, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_my_feature);
    return UNITY_END();
}
```

## Test Naming
- `test_<component>_<behavior>_<condition>`
- Example: `test_monitor_comparison_equal_names`

## Best Practices
✅ Test one thing per test
✅ Use descriptive names
✅ Test edge cases
✅ Follow Arrange-Act-Assert
❌ Don't test Windows API directly
❌ Don't make tests interdependent

## Build & Clean
```bash
make all     # Build all tests
make clean   # Remove artifacts
```

## Test Count: 63
- test_main: 13 tests
- test_monitor: 8 tests
- test_keyboard: 9 tests
- test_shortcuts: 10 tests
- test_desktop: 10 tests
- test_integration: 13 tests

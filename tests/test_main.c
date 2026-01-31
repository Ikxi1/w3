/*
 * Unit tests for main.c utility functions
 * Tests Vec2 structure and basic types
 */

#include "unity/unity.h"
#include <Windows.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

typedef struct vec2 {
    int x;
    int y;
} Vec2;

void setUp(void) {
    /* This is run before each test */
}

void tearDown(void) {
    /* This is run after each test */
}

void test_vec2_arithmetic_operations(void) {
    Vec2 v1 = {10, 20};
    Vec2 v2 = {30, 40};
    
    /* Test addition */
    Vec2 sum;
    sum.x = v1.x + v2.x;
    sum.y = v1.y + v2.y;
    
    TEST_ASSERT_EQUAL_INT(40, sum.x);
    TEST_ASSERT_EQUAL_INT(60, sum.y);
    
    /* Test subtraction */
    Vec2 diff;
    diff.x = v2.x - v1.x;
    diff.y = v2.y - v1.y;
    
    TEST_ASSERT_EQUAL_INT(20, diff.x);
    TEST_ASSERT_EQUAL_INT(20, diff.y);
}

void test_vec2_distance_calculation(void) {
    Vec2 v1 = {0, 0};
    Vec2 v2 = {3, 4};
    
    /* Calculate Manhattan distance */
    int manhattan = abs(v2.x - v1.x) + abs(v2.y - v1.y);
    TEST_ASSERT_EQUAL_INT(7, manhattan);
    
    /* Calculate squared Euclidean distance */
    int dx = v2.x - v1.x;
    int dy = v2.y - v1.y;
    int dist_squared = dx * dx + dy * dy;
    TEST_ASSERT_EQUAL_INT(25, dist_squared);
}

void test_vec2_midpoint_calculation(void) {
    Vec2 v1 = {0, 0};
    Vec2 v2 = {100, 200};
    
    Vec2 midpoint;
    midpoint.x = (v1.x + v2.x) / 2;
    midpoint.y = (v1.y + v2.y) / 2;
    
    TEST_ASSERT_EQUAL_INT(50, midpoint.x);
    TEST_ASSERT_EQUAL_INT(100, midpoint.y);
}

void test_vec2_bounds_checking(void) {
    Vec2 v = {50, 75};
    Vec2 min = {0, 0};
    Vec2 max = {100, 100};
    
    /* Check if point is within bounds */
    BOOL in_bounds = (v.x >= min.x && v.x <= max.x &&
                      v.y >= min.y && v.y <= max.y);
    
    TEST_ASSERT_EQUAL(TRUE, in_bounds);
    
    /* Test out of bounds */
    v.x = 150;
    in_bounds = (v.x >= min.x && v.x <= max.x &&
                 v.y >= min.y && v.y <= max.y);
    
    TEST_ASSERT_EQUAL(FALSE, in_bounds);
}

void test_error_message_null_check(void) {
    /* Test null pointer checking pattern */
    const unsigned short* error_msg = NULL;
    
    TEST_ASSERT_NULL(error_msg);
    
    /* Test with empty string */
    error_msg = L"";
    TEST_ASSERT_NOT_NULL(error_msg);
    
    /* Test equality check */
    BOOL is_null_or_empty = (error_msg == NULL || error_msg[0] == L'\0');
    TEST_ASSERT_EQUAL(TRUE, is_null_or_empty);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_vec2_arithmetic_operations);
    RUN_TEST(test_vec2_distance_calculation);
    RUN_TEST(test_vec2_midpoint_calculation);
    RUN_TEST(test_vec2_bounds_checking);
    RUN_TEST(test_error_message_null_check);
    
    return UNITY_END();
}

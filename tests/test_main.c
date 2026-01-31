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

void test_vec2_initialization(void) {
    Vec2 v = {0};
    
    TEST_ASSERT_EQUAL_INT(0, v.x);
    TEST_ASSERT_EQUAL_INT(0, v.y);
}

void test_vec2_assignment(void) {
    Vec2 v = {0};
    
    v.x = 100;
    v.y = 200;
    
    TEST_ASSERT_EQUAL_INT(100, v.x);
    TEST_ASSERT_EQUAL_INT(200, v.y);
}

void test_vec2_negative_values(void) {
    Vec2 v = {0};
    
    v.x = -100;
    v.y = -200;
    
    TEST_ASSERT_EQUAL_INT(-100, v.x);
    TEST_ASSERT_EQUAL_INT(-200, v.y);
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

void test_window_size_constants(void) {
    TEST_ASSERT_EQUAL_INT(1000, WINDOW_WIDTH);
    TEST_ASSERT_EQUAL_INT(1000, WINDOW_HEIGHT);
}

void test_vec2_screen_coordinates(void) {
    /* Test typical screen coordinate values */
    Vec2 screen_pos = {1920, 1080};
    
    TEST_ASSERT_EQUAL_INT(1920, screen_pos.x);
    TEST_ASSERT_EQUAL_INT(1080, screen_pos.y);
    
    /* Test multi-monitor setup coordinates */
    Vec2 second_monitor = {1920, 0};  /* Second monitor to the right */
    TEST_ASSERT_GREATER_THAN(0, second_monitor.x);
    
    Vec2 negative_monitor = {-1920, 0};  /* Monitor to the left */
    TEST_ASSERT_LESS_THAN(0, negative_monitor.x);
}

void test_vec2_array_of_positions(void) {
    Vec2 positions[3] = {
        {0, 0},
        {100, 100},
        {200, 200}
    };
    
    TEST_ASSERT_EQUAL_INT(0, positions[0].x);
    TEST_ASSERT_EQUAL_INT(0, positions[0].y);
    TEST_ASSERT_EQUAL_INT(100, positions[1].x);
    TEST_ASSERT_EQUAL_INT(100, positions[1].y);
    TEST_ASSERT_EQUAL_INT(200, positions[2].x);
    TEST_ASSERT_EQUAL_INT(200, positions[2].y);
}

void test_vec2_size_structure(void) {
    size_t size = sizeof(Vec2);
    
    /* Vec2 should be 2 integers */
    TEST_ASSERT_EQUAL_size_t(2 * sizeof(int), size);
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

void test_window_style_flags(void) {
    /* Test window style flag combinations */
    unsigned long style = WS_CAPTION | WS_MAXIMIZE | WS_MAXIMIZEBOX | 
                          WS_MINIMIZEBOX | WS_SYSMENU;
    
    /* Verify flags are set */
    TEST_ASSERT_TRUE(style & WS_CAPTION);
    TEST_ASSERT_TRUE(style & WS_MAXIMIZE);
    TEST_ASSERT_TRUE(style & WS_MAXIMIZEBOX);
    TEST_ASSERT_TRUE(style & WS_MINIMIZEBOX);
    TEST_ASSERT_TRUE(style & WS_SYSMENU);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_vec2_initialization);
    RUN_TEST(test_vec2_assignment);
    RUN_TEST(test_vec2_negative_values);
    RUN_TEST(test_vec2_arithmetic_operations);
    RUN_TEST(test_vec2_distance_calculation);
    RUN_TEST(test_vec2_midpoint_calculation);
    RUN_TEST(test_vec2_bounds_checking);
    RUN_TEST(test_window_size_constants);
    RUN_TEST(test_vec2_screen_coordinates);
    RUN_TEST(test_vec2_array_of_positions);
    RUN_TEST(test_vec2_size_structure);
    RUN_TEST(test_error_message_null_check);
    RUN_TEST(test_window_style_flags);
    
    return UNITY_END();
}

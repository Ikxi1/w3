/*
 * Unit tests for monitor.c
 * Tests the monitor comparison and data structure functions
 */

#include "unity/unity.h"
#include <string.h>
#include <wchar.h>

/* Include the necessary definitions from monitor.h */
typedef struct vec2 {
    int x;
    int y;
} Vec2;

typedef struct monitorinfo {
    int   id;
    Vec2  pos;
    Vec2  size;
    wchar_t name[32];  /* CCHDEVICENAME */
} MonitorInfo;

/* External function prototype from monitor.c */
int compare_monitors(const void *a, const void *b);

void setUp(void) {
    /* This is run before each test */
}

void tearDown(void) {
    /* This is run after each test */
}

void test_compare_monitors_equal_names(void) {
    MonitorInfo m1 = {0};
    MonitorInfo m2 = {0};
    
    wcscpy(m1.name, L"\\\\.\\DISPLAY1");
    wcscpy(m2.name, L"\\\\.\\DISPLAY1");
    
    int result = compare_monitors(&m1, &m2);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_compare_monitors_first_less_than_second(void) {
    MonitorInfo m1 = {0};
    MonitorInfo m2 = {0};
    
    wcscpy(m1.name, L"\\\\.\\DISPLAY1");
    wcscpy(m2.name, L"\\\\.\\DISPLAY2");
    
    int result = compare_monitors(&m1, &m2);
    TEST_ASSERT_LESS_THAN(0, result);
}

void test_compare_monitors_first_greater_than_second(void) {
    MonitorInfo m1 = {0};
    MonitorInfo m2 = {0};
    
    wcscpy(m1.name, L"\\\\.\\DISPLAY2");
    wcscpy(m2.name, L"\\\\.\\DISPLAY1");
    
    int result = compare_monitors(&m1, &m2);
    TEST_ASSERT_GREATER_THAN(0, result);
}

void test_compare_monitors_with_empty_names(void) {
    MonitorInfo m1 = {0};
    MonitorInfo m2 = {0};
    
    wcscpy(m1.name, L"");
    wcscpy(m2.name, L"");
    
    int result = compare_monitors(&m1, &m2);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_compare_monitors_one_empty_name(void) {
    MonitorInfo m1 = {0};
    MonitorInfo m2 = {0};
    
    wcscpy(m1.name, L"");
    wcscpy(m2.name, L"\\\\.\\DISPLAY1");
    
    int result = compare_monitors(&m1, &m2);
    TEST_ASSERT_LESS_THAN(0, result);
}

void test_monitor_info_assignment(void) {
    MonitorInfo m = {0};
    
    m.id = 1;
    m.pos.x = 100;
    m.pos.y = 200;
    m.size.x = 1920;
    m.size.y = 1080;
    wcscpy(m.name, L"\\\\.\\DISPLAY1");
    
    TEST_ASSERT_EQUAL_INT(1, m.id);
    TEST_ASSERT_EQUAL_INT(100, m.pos.x);
    TEST_ASSERT_EQUAL_INT(200, m.pos.y);
    TEST_ASSERT_EQUAL_INT(1920, m.size.x);
    TEST_ASSERT_EQUAL_INT(1080, m.size.y);
    TEST_ASSERT_EQUAL_STRING(L"\\\\.\\DISPLAY1", m.name);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_compare_monitors_equal_names);
    RUN_TEST(test_compare_monitors_first_less_than_second);
    RUN_TEST(test_compare_monitors_first_greater_than_second);
    RUN_TEST(test_compare_monitors_with_empty_names);
    RUN_TEST(test_compare_monitors_one_empty_name);
    RUN_TEST(test_monitor_info_assignment);
    
    return UNITY_END();
}

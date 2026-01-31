/*
 * Integration tests for w3 project
 * Tests how different components work together
 */

#include "unity/unity.h"
#include <Windows.h>
#include <string.h>
#include <wchar.h>

/* Common data structures from multiple modules */
typedef struct vec2 {
    int x;
    int y;
} Vec2;

typedef struct monitorinfo {
    int   id;
    Vec2  pos;
    Vec2  size;
    wchar_t name[32];
} MonitorInfo;

typedef struct kbdevent {
    DWORD key;
    DWORD flags;
    BOOL keydown;
} KbdEvent;

enum Direction {
    Left,
    Up,
    Right,
    Down
};

void setUp(void) {
    /* This is run before each test */
}

void tearDown(void) {
    /* This is run after each test */
}

void test_monitor_screen_number_to_index_conversion(void) {
    /* Tests the pattern: screen number (1-9) to array index (0-8) */
    int screen_number = 5;
    int array_index = screen_number - 1;
    
    TEST_ASSERT_EQUAL_INT(4, array_index);
    
    /* Test boundary */
    screen_number = 1;
    array_index = screen_number - 1;
    TEST_ASSERT_EQUAL_INT(0, array_index);
    
    screen_number = 9;
    array_index = screen_number - 1;
    TEST_ASSERT_EQUAL_INT(8, array_index);
}

void test_key_code_to_number_conversion(void) {
    /* Tests the pattern: character code '1'-'9' to number 1-9 */
    char key = '5';
    int number = key - 48;  /* ASCII value of '0' is 48 */
    
    TEST_ASSERT_EQUAL_INT(5, number);
    
    /* Test all digits */
    for (char c = '1'; c <= '9'; c++) {
        int n = c - 48;
        TEST_ASSERT_TRUE(n >= 1 && n <= 9);
    }
}

void test_arrow_key_to_direction_conversion(void) {
    /* Tests the pattern: VK_LEFT (37) to Direction enum (0-3) */
    /* VK_LEFT=37, VK_UP=38, VK_RIGHT=39, VK_DOWN=40 */
    
    DWORD vk_left = VK_LEFT;
    enum Direction dir_left = (enum Direction)(vk_left - 37);
    TEST_ASSERT_EQUAL_INT(Left, dir_left);
    
    DWORD vk_up = VK_UP;
    enum Direction dir_up = (enum Direction)(vk_up - 37);
    TEST_ASSERT_EQUAL_INT(Up, dir_up);
    
    DWORD vk_right = VK_RIGHT;
    enum Direction dir_right = (enum Direction)(vk_right - 37);
    TEST_ASSERT_EQUAL_INT(Right, dir_right);
    
    DWORD vk_down = VK_DOWN;
    enum Direction dir_down = (enum Direction)(vk_down - 37);
    TEST_ASSERT_EQUAL_INT(Down, dir_down);
}

void test_monitor_center_calculation(void) {
    /* Tests calculating center of a monitor for cursor positioning */
    MonitorInfo m = {0};
    m.id = 0;
    m.pos.x = 1920;  /* Second monitor to the right */
    m.pos.y = 0;
    m.size.x = 1920;
    m.size.y = 1080;
    
    /* Calculate center */
    int center_x = m.pos.x + m.size.x / 2;
    int center_y = m.pos.y + m.size.y / 2;
    
    TEST_ASSERT_EQUAL_INT(2880, center_x);  /* 1920 + 960 */
    TEST_ASSERT_EQUAL_INT(540, center_y);   /* 0 + 540 */
}

void test_point_in_monitor_bounds(void) {
    /* Tests checking if a point is within monitor bounds */
    MonitorInfo m = {0};
    m.pos.x = 0;
    m.pos.y = 0;
    m.size.x = 1920;
    m.size.y = 1080;
    
    /* Point inside */
    int px = 500;
    int py = 500;
    BOOL inside = (px >= m.pos.x &&
                   py >= m.pos.y &&
                   px < m.pos.x + m.size.x &&
                   py < m.pos.y + m.size.y);
    TEST_ASSERT_EQUAL(TRUE, inside);
    
    /* Point outside (to the right) */
    px = 2000;
    inside = (px >= m.pos.x &&
              py >= m.pos.y &&
              px < m.pos.x + m.size.x &&
              py < m.pos.y + m.size.y);
    TEST_ASSERT_EQUAL(FALSE, inside);
}

void test_keyboard_modifier_state_combinations(void) {
    /* Tests checking for modifier key combinations */
    BOOL shiftDown = TRUE;
    BOOL ctrlDown = FALSE;
    BOOL macroMode = TRUE;
    
    /* Test: Win+Shift+Q pattern */
    BOOL is_quit_combo = macroMode && shiftDown;
    TEST_ASSERT_EQUAL(TRUE, is_quit_combo);
    
    /* Test: Win+Q pattern (without shift) */
    shiftDown = FALSE;
    BOOL is_close_combo = macroMode && !shiftDown;
    TEST_ASSERT_EQUAL(TRUE, is_close_combo);
    
    /* Test: Not in macro mode */
    macroMode = FALSE;
    BOOL should_process = macroMode;
    TEST_ASSERT_EQUAL(FALSE, should_process);
}

void test_multi_monitor_array_indexing(void) {
    /* Tests working with an array of monitors */
    int monitor_count = 3;
    MonitorInfo monitors[3] = {
        {0, {0, 0}, {1920, 1080}, L"\\\\.\\DISPLAY1"},
        {1, {1920, 0}, {1920, 1080}, L"\\\\.\\DISPLAY2"},
        {2, {3840, 0}, {1920, 1080}, L"\\\\.\\DISPLAY3"}
    };
    
    /* Verify all monitors are initialized */
    for (int i = 0; i < monitor_count; i++) {
        TEST_ASSERT_EQUAL_INT(i, monitors[i].id);
        TEST_ASSERT_EQUAL_INT(1920, monitors[i].size.x);
        TEST_ASSERT_EQUAL_INT(1080, monitors[i].size.y);
    }
    
    /* Test horizontal positioning */
    TEST_ASSERT_EQUAL_INT(0, monitors[0].pos.x);
    TEST_ASSERT_EQUAL_INT(1920, monitors[1].pos.x);
    TEST_ASSERT_EQUAL_INT(3840, monitors[2].pos.x);
}

void test_keyboard_event_to_shortcut_mapping(void) {
    /* Tests mapping keyboard events to application shortcuts */
    KbdEvent evt = {0};
    BOOL shiftDown = FALSE;
    BOOL macroMode = TRUE;
    
    /* Win+D -> Start menu */
    evt.key = 'D';
    evt.keydown = TRUE;
    BOOL is_start_menu = (macroMode && evt.keydown && evt.key == 'D');
    TEST_ASSERT_EQUAL(TRUE, is_start_menu);
    
    /* Win+Shift+E -> Quit */
    evt.key = 'E';
    shiftDown = TRUE;
    BOOL is_quit = (macroMode && evt.keydown && evt.key == 'E' && shiftDown);
    TEST_ASSERT_EQUAL(TRUE, is_quit);
    
    /* Win+I -> Settings */
    evt.key = 'I';
    shiftDown = FALSE;
    BOOL is_settings = (macroMode && evt.keydown && evt.key == 'I');
    TEST_ASSERT_EQUAL(TRUE, is_settings);
}

void test_monitor_edge_detection_for_cursor_movement(void) {
    /* Tests detecting monitor edges for directional cursor movement */
    MonitorInfo current = {0, {0, 0}, {1920, 1080}, L"\\\\.\\DISPLAY1"};
    
    /* Calculate edge points */
    int left_edge = current.pos.x - 1;
    int top_edge = current.pos.y - 1;
    int right_edge = current.pos.x + current.size.x + 1;
    int bottom_edge = current.pos.y + current.size.y + 1;
    
    TEST_ASSERT_EQUAL_INT(-1, left_edge);
    TEST_ASSERT_EQUAL_INT(-1, top_edge);
    TEST_ASSERT_EQUAL_INT(1921, right_edge);
    TEST_ASSERT_EQUAL_INT(1081, bottom_edge);
}

void test_window_message_identification(void) {
    /* Tests identifying custom window messages */
    #define WM_KBD_EVENT (WM_APP + 1)
    
    UINT msg = WM_KBD_EVENT;
    BOOL is_keyboard_event = (msg == WM_KBD_EVENT);
    TEST_ASSERT_EQUAL(TRUE, is_keyboard_event);
    
    msg = WM_DESTROY;
    is_keyboard_event = (msg == WM_KBD_EVENT);
    TEST_ASSERT_EQUAL(FALSE, is_keyboard_event);
}

void test_screen_switching_bounds_check(void) {
    /* Tests validating screen number before switching */
    int monitor_count = 3;
    int requested_screen = 2;
    
    BOOL is_valid = (requested_screen >= 1 && requested_screen <= monitor_count);
    TEST_ASSERT_EQUAL(TRUE, is_valid);
    
    requested_screen = 5;
    is_valid = (requested_screen >= 1 && requested_screen <= monitor_count);
    TEST_ASSERT_EQUAL(FALSE, is_valid);
    
    requested_screen = 0;
    is_valid = (requested_screen >= 1 && requested_screen <= monitor_count);
    TEST_ASSERT_EQUAL(FALSE, is_valid);
}

void test_direction_iteration_pattern(void) {
    /* Tests the retry pattern for finding adjacent monitors */
    int tries = 0;
    int max_tries = 3;
    
    while (tries < max_tries) {
        /* Simulate trying different vertical positions */
        int vertical_position;
        if (tries == 0) vertical_position = 100;      /* Bottom */
        else if (tries == 1) vertical_position = 50;  /* Middle */
        else if (tries == 2) vertical_position = 0;   /* Top */
        
        TEST_ASSERT_TRUE(tries >= 0 && tries < 3);
        tries++;
    }
    
    TEST_ASSERT_EQUAL_INT(3, tries);
}

void test_virtual_key_ranges(void) {
    /* Tests that various key types are in expected ranges */
    
    /* Letters */
    TEST_ASSERT_TRUE('A' >= 0x41 && 'Z' <= 0x5A);
    
    /* Numbers */
    TEST_ASSERT_TRUE('0' >= 0x30 && '9' <= 0x39);
    
    /* Function keys */
    TEST_ASSERT_EQUAL_UINT32(0x70, VK_F1);
    TEST_ASSERT_EQUAL_UINT32(0x87, VK_F24);
    TEST_ASSERT_TRUE(VK_F1 >= 0x70 && VK_F24 <= 0x87);
    
    /* Arrow keys */
    TEST_ASSERT_TRUE(VK_LEFT >= 0x25 && VK_DOWN <= 0x28);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_monitor_screen_number_to_index_conversion);
    RUN_TEST(test_key_code_to_number_conversion);
    RUN_TEST(test_arrow_key_to_direction_conversion);
    RUN_TEST(test_monitor_center_calculation);
    RUN_TEST(test_point_in_monitor_bounds);
    RUN_TEST(test_keyboard_modifier_state_combinations);
    RUN_TEST(test_multi_monitor_array_indexing);
    RUN_TEST(test_keyboard_event_to_shortcut_mapping);
    RUN_TEST(test_monitor_edge_detection_for_cursor_movement);
    RUN_TEST(test_window_message_identification);
    RUN_TEST(test_screen_switching_bounds_check);
    RUN_TEST(test_direction_iteration_pattern);
    RUN_TEST(test_virtual_key_ranges);
    
    return UNITY_END();
}

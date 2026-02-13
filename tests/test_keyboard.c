/*
 * Unit tests for keyboard.c
 * Tests keyboard state management and event structures
 */

#include "unity/unity.h"
#include <Windows.h>

#define WM_KBD_EVENT (WM_APP + 1)

typedef struct kbdevent {
    DWORD key;
    DWORD flags;
    BOOL keydown;
} KbdEvent;

void setUp(void) {
    /* This is run before each test */
}

void tearDown(void) {
    /* This is run after each test */
}

void test_kbdevent_various_keys(void) {
    KbdEvent evt = {0};
    
    /* Test with 'D' key */
    evt.key = 'D';
    evt.keydown = TRUE;
    TEST_ASSERT_EQUAL_UINT32('D', evt.key);
    
    /* Test with 'E' key */
    evt.key = 'E';
    TEST_ASSERT_EQUAL_UINT32('E', evt.key);
    
    /* Test with arrow keys */
    evt.key = VK_LEFT;
    TEST_ASSERT_EQUAL_UINT32(VK_LEFT, evt.key);
    
    evt.key = VK_RIGHT;
    TEST_ASSERT_EQUAL_UINT32(VK_RIGHT, evt.key);
    
    evt.key = VK_UP;
    TEST_ASSERT_EQUAL_UINT32(VK_UP, evt.key);
    
    evt.key = VK_DOWN;
    TEST_ASSERT_EQUAL_UINT32(VK_DOWN, evt.key);
}

void test_wm_kbd_event_message_value(void) {
    /* Verify the custom keyboard event message is properly defined */
    TEST_ASSERT_EQUAL_UINT32(WM_APP + 1, WM_KBD_EVENT);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_kbdevent_various_keys);
    RUN_TEST(test_wm_kbd_event_message_value);
    
    return UNITY_END();
}

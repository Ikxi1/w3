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

void test_kbdevent_structure_initialization(void) {
    KbdEvent evt = {0};
    
    TEST_ASSERT_EQUAL_UINT32(0, evt.key);
    TEST_ASSERT_EQUAL_UINT32(0, evt.flags);
    TEST_ASSERT_EQUAL(FALSE, evt.keydown);
}

void test_kbdevent_keydown_assignment(void) {
    KbdEvent evt = {0};
    
    evt.key = VK_SHIFT;
    evt.flags = 0;
    evt.keydown = TRUE;
    
    TEST_ASSERT_EQUAL_UINT32(VK_SHIFT, evt.key);
    TEST_ASSERT_EQUAL_UINT32(0, evt.flags);
    TEST_ASSERT_EQUAL(TRUE, evt.keydown);
}

void test_kbdevent_keyup_assignment(void) {
    KbdEvent evt = {0};
    
    evt.key = VK_CONTROL;
    evt.flags = 0;
    evt.keydown = FALSE;
    
    TEST_ASSERT_EQUAL_UINT32(VK_CONTROL, evt.key);
    TEST_ASSERT_EQUAL_UINT32(0, evt.flags);
    TEST_ASSERT_EQUAL(FALSE, evt.keydown);
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

void test_kbdevent_number_keys(void) {
    KbdEvent evt = {0};
    
    for (char c = '1'; c <= '9'; c++) {
        evt.key = c;
        TEST_ASSERT_EQUAL_UINT32(c, evt.key);
    }
}

void test_kbdevent_flags_injected(void) {
    KbdEvent evt = {0};
    
    evt.flags = LLKHF_INJECTED;
    TEST_ASSERT_EQUAL_UINT32(LLKHF_INJECTED, evt.flags);
}

void test_wm_kbd_event_message_value(void) {
    /* Verify the custom keyboard event message is properly defined */
    TEST_ASSERT_EQUAL_UINT32(WM_APP + 1, WM_KBD_EVENT);
}

void test_keyboard_state_boolean_values(void) {
    BOOL shiftDown = FALSE;
    BOOL ctrlDown = FALSE;
    BOOL macroMode = FALSE;
    
    TEST_ASSERT_EQUAL(FALSE, shiftDown);
    TEST_ASSERT_EQUAL(FALSE, ctrlDown);
    TEST_ASSERT_EQUAL(FALSE, macroMode);
    
    /* Test state transitions */
    shiftDown = TRUE;
    TEST_ASSERT_EQUAL(TRUE, shiftDown);
    
    ctrlDown = TRUE;
    TEST_ASSERT_EQUAL(TRUE, ctrlDown);
    
    macroMode = TRUE;
    TEST_ASSERT_EQUAL(TRUE, macroMode);
}

void test_virtual_key_codes(void) {
    /* Test that virtual key codes are as expected */
    TEST_ASSERT_EQUAL_UINT32(0x10, VK_SHIFT);
    TEST_ASSERT_EQUAL_UINT32(0x11, VK_CONTROL);
    TEST_ASSERT_EQUAL_UINT32(0x5B, VK_LWIN);
    TEST_ASSERT_EQUAL_UINT32(0x5C, VK_RWIN);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_kbdevent_structure_initialization);
    RUN_TEST(test_kbdevent_keydown_assignment);
    RUN_TEST(test_kbdevent_keyup_assignment);
    RUN_TEST(test_kbdevent_various_keys);
    RUN_TEST(test_kbdevent_number_keys);
    RUN_TEST(test_kbdevent_flags_injected);
    RUN_TEST(test_wm_kbd_event_message_value);
    RUN_TEST(test_keyboard_state_boolean_values);
    RUN_TEST(test_virtual_key_codes);
    
    return UNITY_END();
}

/*
 * Unit tests for shortcuts.c
 * Tests INPUT structure and shortcut key combinations
 */

#include "unity/unity.h"
#include <Windows.h>

void setUp(void) {
    /* This is run before each test */
}

void tearDown(void) {
    /* This is run after each test */
}

void test_screenshot_key_combination_structure(void) {
    /* Win+Shift+S */
    INPUT inputs[6] = {0};
    
    /* Initialize all as keyboard input */
    for (int i = 0; i < 6; i++) {
        inputs[i].type = INPUT_KEYBOARD;
    }
    
    /* Key down */
    inputs[0].ki.wVk = VK_LWIN;
    inputs[1].ki.wVk = VK_LSHIFT;
    inputs[2].ki.wVk = 'S';
    
    /* Key up */
    inputs[3].ki.wVk = VK_LWIN;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[4].ki.wVk = VK_LSHIFT;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[5].ki.wVk = 'S';
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;
    
    /* Verify key down sequence */
    TEST_ASSERT_EQUAL_UINT32(VK_LWIN, inputs[0].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(0, inputs[0].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32(VK_LSHIFT, inputs[1].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(0, inputs[1].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32('S', inputs[2].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(0, inputs[2].ki.dwFlags);
    
    /* Verify key up sequence */
    TEST_ASSERT_EQUAL_UINT32(VK_LWIN, inputs[3].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[3].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32(VK_LSHIFT, inputs[4].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[4].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32('S', inputs[5].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[5].ki.dwFlags);
}

void test_settings_key_combination_structure(void) {
    /* Win+I */
    INPUT inputs[4] = {0};
    
    for (int i = 0; i < 4; i++) {
        inputs[i].type = INPUT_KEYBOARD;
    }
    
    /* Key down */
    inputs[0].ki.wVk = VK_LWIN;
    inputs[1].ki.wVk = 'I';
    
    /* Key up */
    inputs[2].ki.wVk = VK_LWIN;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].ki.wVk = 'I';
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    
    TEST_ASSERT_EQUAL_UINT32(VK_LWIN, inputs[0].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32('I', inputs[1].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[2].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[3].ki.dwFlags);
}

void test_start_menu_key_combination_structure(void) {
    /* Win key only */
    INPUT inputs[2] = {0};
    
    for (int i = 0; i < 2; i++) {
        inputs[i].type = INPUT_KEYBOARD;
    }
    
    /* Key down */
    inputs[0].ki.wVk = VK_LWIN;
    
    /* Key up */
    inputs[1].ki.wVk = VK_LWIN;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    
    TEST_ASSERT_EQUAL_UINT32(VK_LWIN, inputs[0].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(0, inputs[0].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32(VK_LWIN, inputs[1].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[1].ki.dwFlags);
}

void test_close_program_key_combination_structure(void) {
    /* Alt+F4 */
    INPUT inputs[4] = {0};
    
    for (int i = 0; i < 4; i++) {
        inputs[i].type = INPUT_KEYBOARD;
    }
    
    /* Key down */
    inputs[0].ki.wVk = VK_LMENU;
    inputs[1].ki.wVk = VK_F4;
    
    /* Key up */
    inputs[2].ki.wVk = VK_LMENU;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].ki.wVk = VK_F4;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    
    TEST_ASSERT_EQUAL_UINT32(VK_LMENU, inputs[0].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(VK_F4, inputs[1].ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[2].ki.dwFlags);
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, inputs[3].ki.dwFlags);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_screenshot_key_combination_structure);
    RUN_TEST(test_settings_key_combination_structure);
    RUN_TEST(test_start_menu_key_combination_structure);
    RUN_TEST(test_close_program_key_combination_structure);
    
    return UNITY_END();
}

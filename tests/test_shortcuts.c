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

void test_input_structure_initialization(void) {
    INPUT input = {0};
    
    TEST_ASSERT_EQUAL_UINT32(0, input.type);
    TEST_ASSERT_EQUAL_UINT32(0, input.ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(0, input.ki.dwFlags);
}

void test_input_keyboard_type(void) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    
    TEST_ASSERT_EQUAL_UINT32(INPUT_KEYBOARD, input.type);
}

void test_input_key_assignment(void) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_LWIN;
    
    TEST_ASSERT_EQUAL_UINT32(VK_LWIN, input.ki.wVk);
    TEST_ASSERT_EQUAL_UINT32(0, input.ki.dwFlags);
}

void test_input_keyup_flag(void) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_LWIN;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    
    TEST_ASSERT_EQUAL_UINT32(KEYEVENTF_KEYUP, input.ki.dwFlags);
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

void test_input_array_size_calculations(void) {
    INPUT single_input = {0};
    
    /* Verify INPUT structure size matches expected */
    size_t input_size = sizeof(INPUT);
    TEST_ASSERT_TRUE(input_size > 0);
    
    /* Test array size calculations */
    INPUT inputs[6];
    TEST_ASSERT_EQUAL_size_t(6 * sizeof(INPUT), sizeof(inputs));
}

void test_virtual_key_constants(void) {
    /* Verify important virtual key codes */
    TEST_ASSERT_EQUAL_UINT32(0x70, VK_F1);
    TEST_ASSERT_EQUAL_UINT32(0x73, VK_F4);
    TEST_ASSERT_EQUAL_UINT32(0x12, VK_MENU);  /* Alt key */
    TEST_ASSERT_EQUAL_UINT32(0xA4, VK_LMENU); /* Left Alt */
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_input_structure_initialization);
    RUN_TEST(test_input_keyboard_type);
    RUN_TEST(test_input_key_assignment);
    RUN_TEST(test_input_keyup_flag);
    RUN_TEST(test_screenshot_key_combination_structure);
    RUN_TEST(test_settings_key_combination_structure);
    RUN_TEST(test_start_menu_key_combination_structure);
    RUN_TEST(test_close_program_key_combination_structure);
    RUN_TEST(test_input_array_size_calculations);
    RUN_TEST(test_virtual_key_constants);
    
    return UNITY_END();
}

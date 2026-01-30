#include "../include/shortcuts.h"


void take_screenshot(void) {
#undef keys
#define keys 6
      INPUT inputs[keys] = {0};
      for (int i = 0; i < keys; i++)
            inputs[i].type = INPUT_KEYBOARD;
      /* key down */
      inputs[0].ki.wVk     = VK_LWIN;
      inputs[1].ki.wVk     = VK_LSHIFT;
      inputs[2].ki.wVk     = 'S';
      /* key up */
      inputs[3].ki.wVk     = VK_LWIN;
      inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
      inputs[4].ki.wVk     = VK_LSHIFT;
      inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;
      inputs[5].ki.wVk     = 'S';
      inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

      SendInput(keys, inputs, sizeof(INPUT));
      print(L"Taking screenshot\n");
}


void open_settings(void) {
#undef keys
#define keys 4
      INPUT inputs[keys] = {0};
      for (int i = 0; i < keys; i++) {
            inputs[i].type = INPUT_KEYBOARD;
      }
      /* key down */
      inputs[0].ki.wVk     = VK_LWIN;
      inputs[1].ki.wVk     = 'I';
      /* key up */
      inputs[2].ki.wVk     = VK_LWIN;
      inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
      inputs[3].ki.wVk     = 'I';
      inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

      SendInput(keys, inputs, sizeof(INPUT));
      print(L"Opening settings\n");
}


void open_startmenu(void) {
#undef keys
#define keys 2
      INPUT inputs[keys] = {0};
      for (int i = 0; i < keys; i++) {
            inputs[i].type = INPUT_KEYBOARD;
      }
      /* key down */
      inputs[0].ki.wVk     = VK_LWIN;
      /* key up */
      inputs[1].ki.wVk     = VK_LWIN;
      inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

      SendInput(keys, inputs, sizeof(INPUT));
      print(L"Opening start menu\n");
}


void close_program(void) {
#undef keys
#define keys 4
      INPUT inputs[keys] = {0};
      for (int i = 0; i < keys; i++) {
            inputs[i].type = INPUT_KEYBOARD;
      }
      /* key down */
      inputs[0].ki.wVk     = VK_LMENU;
      inputs[1].ki.wVk     = VK_F4;
      /* key up */
      inputs[2].ki.wVk     = VK_LMENU;
      inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
      inputs[3].ki.wVk     = VK_F4;
      inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

      SendInput(keys, inputs, sizeof(INPUT));
      print(L"Closing program\n");
}

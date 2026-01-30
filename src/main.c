/*
 * Author: Ikxi
 * Date: 24.01.2026
 */

#include "../include/main.h"
#include "../include/extra.h"
#include "../include/keyboard.h"
#include "../include/monitor.h"
#include "../include/shortcuts.h"


// BOOL CALLBACK EnumDesktopProc(LPTSTR desktop, LPARAM lParam) {
//       desktop;
//
//       return TRUE;
// };


int WINAPI wmain(void) {

      print(L"mission starto!\n");
      print(L"Running a debug build!\n");

      /* initialize main window */
      hInstance        = GetModuleHandle(NULL);
      WNDCLASS wc      = {0};
      wc.lpfnWndProc   = WndProc;
      wc.hInstance     = hInstance;
      wc.lpszClassName = L"MainWindow";
      RegisterClass(&wc);

      unsigned long style = WS_CAPTION | WS_MAXIMIZE | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU;
      mainWindow = CreateWindowEx(
            0,
            L"MainWindow",
            L"Testing",
            style,
            CW_USEDEFAULT, CW_USEDEFAULT,
            0, 0,
            NULL, NULL,
            wc.hInstance, NULL
      );
      if (mainWindow == NULL) {
            error_exit(L"Couldn't create a main window.");
            return -1;
      }

      ShowWindow(mainWindow, SW_HIDE);
#ifdef _DEBUG
      ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
      ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // _DEBUG

      get_monitors();

      /* Set up low level keyboard hook */
      kbdHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
      if (!kbdHook) { error_exit(L"Failed to install keyboard hook\n"); }

      SetTimer(mainWindow, 1, 1000, NULL);

      /*
       * main loop
       * event management in WndProc()
       */
      MSG msg;
      while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
      }

      print(L"otsu\n");
      return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
      switch (msg) {
            case WM_CREATE: {
                  break;
            }

            case WM_KBD_EVENT: {
                  KbdEvent* e = (KbdEvent*)lParam;
                  if (macroMode && e->keydown) {
                        // if (e->key != 91) {print(L"%i\n",e->key);}
                        switch (e->key) {
                              case 'D': {
                                    open_startmenu();
                                    break;
                              }

                              case 'E': {
                                    if (shiftDown == TRUE) {
                                          print(L"Quitting\n");
                                          PostQuitMessage(0);
                                    }
                                    break;
                              }

                              case 'I': {
                                    open_settings();
                                    break;
                              }

                              case 'Q': {
                                    if (shiftDown == TRUE) close_program();
                                    break;
                              }

                              case 'S': {
                                    if (shiftDown == TRUE) take_screenshot();
                                    break;
                              }

                              /* switch between monitors */
                              case '1':
                              case '2':
                              case '3':
                              case '4':
                              case '5':
                              case '6':
                              case '7':
                              case '8':
                              case '9': {
                                    if (shiftDown == TRUE) {
                                          switch_program_to_screen(e->key - 48);
                                          break;
                                    }
                                    switch_cursor_to_screen(e->key - 48);
                                    break;
                              }
                              /*
                              * 37 left
                              * 38 up
                              * 39 right
                              * 40 down
                              */
                              /* move cursor between monitors */
                              case VK_LEFT:
                              case VK_UP:
                              case VK_RIGHT:
                              case VK_DOWN: {
                                    if (shiftDown == TRUE) {
                                          move_program_to_screen((enum Level)(e->key - 37));
                                          break;
                                    }
                                    move_cursor_to_screen((enum Level)(e->key - 37));
                                    break;
                              }

                              default: break;
                        }
                  }
                  if (e) { HeapFree(GetProcessHeap(), 0, e); }
                  return 0;
            }

            case WM_TIMER: {
                  /*
                   * this can be turned on, if you want it to recognize when
                   * a monitor gets added or removed
                   */
                  // destroy_monitors();
                  // monitorID = 0;
                  // get_monitors();
                  return 0;
            }

            case WM_DESTROY: {
                  destroy_monitors();
                  PostQuitMessage((int)wParam);
                  return 0;
            }
            default: break;
      }
      return DefWindowProc(hwnd, msg, wParam, lParam);
}


void error_exit(const unsigned short* error_msg) {
#ifndef _DEBUG
      ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
      if (error_msg == NULL || error_msg == L"") {
            error_msg = L"No error specified";
      }
      fwprintf_s(stderr, error_msg);
      PostQuitMessage(-1);
}

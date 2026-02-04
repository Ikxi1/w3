/*
 * Author: Ikxi
 * Date: 24.01.2026
 */

#include "../include/main.h"
#include "../include/extra.h"
#include "../include/keyboard.h"
#include "../include/monitor.h"
#include "../include/extra.h"

#include <stdio.h>
#include <stdlib.h>


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
                  KbdEvent *e = (KbdEvent*)lParam;
                  kbd_process(e);
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

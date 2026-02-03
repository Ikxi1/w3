#pragma once

#include <Windows.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

HWND      mainWindow;
HINSTANCE hInstance;

typedef struct vec2 {
      int x;
      int y;
} Vec2;


/*
Receives all WM_ message events and processes them.

THIS FUNCTION IS NOT TO BE CALLED DIRECTLY.

Input:
      These are all managed by WinAPI

Output:
      This is only for WinAPI

Modifies:
      Basically everything
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
Safely closes the program with a specified error message.

Input:
      error_msg: const unsigned short*
            - A wide string containing details
              about the error
            - can be NULL

Output:
      None

Modifies:
      Everything, cause it quits.

 */
void error_exit(const unsigned short *error_msg);

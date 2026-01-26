#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "extra.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

HWND mainWindow;
HINSTANCE hInstance;

typedef struct vec2 {
      int x;
      int y;
} Vec2;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
void error_exit( unsigned short *error_msg );
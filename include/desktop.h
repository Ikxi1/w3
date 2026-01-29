#pragma once

#include "main.h"


typedef struct {
      HWND hwnd;
      DWORD pid;
      WCHAR title[512];
      int z_order; /* 0 = topmost, increases downward */
      int monitor_id; /* -1 = unknown */
} AppWindow;

typedef struct {
      AppWindow* items;
      size_t count;
} AppList;

void getOpenWindows();

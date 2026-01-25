#pragma once

#include "main.h"

#define WM_KBD_EVENT (WM_APP + 1)

HHOOK kbd_hook;

extern BOOL shiftDown;
extern BOOL ctrlDown;

typedef struct kbdevent {
      DWORD key;
      DWORD flags;
      BOOL keydown;
} KbdEvent;

extern KbdEvent *lastEvent;

LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );

#pragma once

#include "main.h"

#define WM_KBD_EVENT ( WM_APP + 1 )

HHOOK kbdHook;

extern BOOL shiftDown;
extern BOOL ctrlDown;
extern BOOL macroMode;

typedef struct kbdevent {
      DWORD key;
      DWORD flags;
      BOOL keydown;
} KbdEvent;

extern KbdEvent* lastEvent;

LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );

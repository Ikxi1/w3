#pragma once

#include "main.h"

HHOOK kbd_hook;

extern BOOL shiftDown;
extern BOOL ctrlDown;

typedef struct kbdevent {
      DWORD key;
      DWORD flags;
      BOOL keydown;
} KbdEvent;

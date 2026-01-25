#include "keyboard.h"


LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam ) {
      if ( nCode < 0 ) { return CallNextHookEx( kbd_hook, nCode, wParam, lParam ); }

      KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;

      if ( kbd->flags & LLKHF_INJECTED ) { return CallNextHookEx( kbd_hook, nCode, wParam, lParam ); }

      BOOL keydown = ( wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN );
      BOOL keyup = ( wParam == WM_KEYUP || wParam == WM_SYSKEYUP );

      DWORD key = kbd->vkCode;

      if ( key == VK_SHIFT ) {
            if ( keydown ) shiftDown = TRUE;
            if ( keyup ) shiftDown = FALSE;
      }
      if ( key == VK_CONTROL ) {
            if ( keydown ) ctrlDown = TRUE;
            if ( keyup ) ctrlDown = FALSE;
      }

      KbdEvent *evt = (KbdEvent *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof( KbdEvent ) );

      if ( evt ) {
            evt->key = key;
            evt->flags = kbd->flags;
            evt->keydown = keydown;
            PostMessage( mainWindow, WM_KBD_EVENT, 0, (LPARAM)evt );
      }

      return CallNextHookEx( kbd_hook, nCode, wParam, lParam );
}

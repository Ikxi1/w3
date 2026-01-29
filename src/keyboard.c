#include "../include/keyboard.h"
#include "../include/extra.h"


BOOL shiftDown = FALSE;
BOOL ctrlDown = FALSE;
BOOL macroMode = FALSE;


LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam ) {
      if ( nCode < 0 ) { return CallNextHookEx( kbdHook, nCode, wParam, lParam ); }

      KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;

      if ( kbd->flags & LLKHF_INJECTED ) { return CallNextHookEx( kbdHook, nCode, wParam, lParam ); }

      BOOL keydown = ( wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN );
      BOOL keyup = ( wParam == WM_KEYUP || wParam == WM_SYSKEYUP );

      DWORD key = kbd->vkCode;

      if ( /*key == VK_SHIFT ||*/ key == VK_LSHIFT || key == VK_RSHIFT ) {
            if ( keydown ) shiftDown = TRUE;
            if ( keyup ) shiftDown = FALSE;
      }
      if ( /*key == VK_CONTROL ||*/ key == VK_LCONTROL || key == VK_RCONTROL ) {
            if ( keydown ) ctrlDown = TRUE;
            if ( keyup ) ctrlDown = FALSE;
      }

      KbdEvent* evt = (KbdEvent*)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof( KbdEvent ) );

      if ( evt ) {
            evt->key = key;
            evt->flags = kbd->flags;
            evt->keydown = keydown;
            PostMessage( mainWindow, WM_KBD_EVENT, 0, (LPARAM)evt );
      }

      /* if Win-Key pressed, swallow the event*/
      if ( keydown && ( key == VK_LWIN || key == VK_RWIN ) ) {
            macroMode = TRUE;
            // print( L"Macro mode on\n" );
            return 1;
      } else if ( keyup && ( key == VK_LWIN || key == VK_RWIN ) ) {
            macroMode = FALSE;
            // print( L"Macro mode off\n" );
            return 1;
      }

      /* Swallow any keyboard events, when macroMode is one */
      if ( macroMode ) return 1;

      return CallNextHookEx( kbdHook, nCode, wParam, lParam );
}

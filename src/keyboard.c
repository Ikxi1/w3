#include "../include/keyboard.h"
#include "../include/extra.h"
#include "../include/shortcuts.h"
#include "../include/monitor.h"
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


void kbd_process(KbdEvent *event) {
      if (macroMode && event->keydown) {
                        // if (e->key != 91) {print(L"%i\n",e->key);}
                        switch (event->key) {
                              case 'D': {
                                    open_startmenu();
                                    break;
                              }

                              case 'E': {
                                    if (shiftDown == TRUE) {
                                          print(L"Quitting\n");
                                          PostQuitMessage(0);
                                          break;
                                    }
                                    open_file_explorer();
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
                                          switch_program_to_screen(event->key - 48);
                                          break;
                                    }
                                    switch_cursor_to_screen(event->key - 48);
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
                                          move_program_to_screen((enum Level)(event->key - 37));
                                          break;
                                    }
                                    move_cursor_to_screen((enum Level)(event->key - 37));
                                    break;
                              }

                              default: break;
                        }
                  }
}

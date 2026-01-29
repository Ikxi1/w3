/*
* Author: Ikxi
* Date: 24.01.2026
*/

#include "main.h"
#include "monitor.h"
#include "extra.h"
#include "keyboard.h"


BOOL CALLBACK EnumDesktopProc( LPTSTR desktop, LPARAM lParam ) {
      desktop;

      return TRUE;
};


int WINAPI wmain(void) {

      print( L"mission starto!\n" );
#ifdef _DEBUG
      print( L"Running a debug build!\n" );
#endif

      /* initialize main window */
      hInstance = GetModuleHandle(NULL);
      WNDCLASS wc = {0};
      wc.lpfnWndProc = WndProc;
      wc.hInstance = hInstance;
      wc.lpszClassName = L"MainWindow";
      RegisterClass( &wc );

      unsigned long style = WS_CAPTION | WS_MAXIMIZE | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU;
      mainWindow = CreateWindowEx(
            0,
            L"MainWindow",
            L"Testing",
            style,
            CW_USEDEFAULT, CW_USEDEFAULT,
            0, 0,
            NULL, NULL,
            wc.hInstance, NULL );
      if ( mainWindow == NULL ) { error_exit( L"Couldn't create a main window." ); return -1; }
      
      ShowWindow( mainWindow, SW_HIDE );
#ifdef _DEBUG
      ShowWindow( GetConsoleWindow(), SW_SHOW );
#else
      ShowWindow( GetConsoleWindow(), SW_HIDE );
#endif // _DEBUG

      get_monitors();

      /* Set up low level keyboard hook */
      kbdHook = SetWindowsHookEx(
            WH_KEYBOARD_LL,
            LowLevelKeyboardProc,
            NULL,
            0
      );
      if ( !kbdHook ) { error_exit( L"Failed to install keyboard hook\n" ); }

      SetTimer( mainWindow, 1, 1000, NULL );

      /*
      * main loop
      * event management in WndProc() 
      */
      MSG msg;
      while ( GetMessage( &msg, NULL, 0, 0 ) ) {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
      }

      print(L"otsu\n");
      return 0;
}


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
      switch ( msg ) {
            case WM_CREATE: {
                  break;
            }

            case WM_KBD_EVENT: {
                  KbdEvent *e = (KbdEvent *)lParam;
                  if ( macroMode && e->keydown ) {
                        switch ( e->key ) {
                              case 'E': {
                                    if ( shiftDown == TRUE ) {
#ifdef _DEBUG
                                          print( L"Quitting\n" );
#endif
                                          PostQuitMessage( 0 );
                                    }
                                    break;
                              }

                              case 'D': {
                                    // doesn't work right now
                                    // CreateDesktop( L"Desktop2", NULL, NULL, 0, GENERIC_ALL, NULL );
                                    break;
                              }

                              case 'S': {
                                    if ( shiftDown == TRUE ) take_screenshot();
                                    break;
                              }

                               /* switch between monitors */
                              case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: {
                                    
                                    break;
                              }
                              default: break;
                        }
                  }
                  if ( e ) { HeapFree( GetProcessHeap(), 0, e ); }
                  return 0;
            }

            case WM_TIMER: {
                  /*
                  * this can be turned on, if you want it to recognize when
                  * a monitor gets added or removed
                  */
                  //monitorID = 0;
                  //get_monitors();
                  return 0;
            }

            case WM_DESTROY: {
                  destroy_monitors();
                  PostQuitMessage( (int)wParam );
                  return 0;
            }
            default:
                  break;
      }
      return DefWindowProc( hwnd, msg, wParam, lParam );
}


void error_exit( unsigned short *error_msg ) {
#ifndef _DEBUG
      ShowWindow( GetConsoleWindow(), SW_SHOW );
#endif
      fwprintf( stderr, error_msg );
      PostQuitMessage( -1 );
}


void take_screenshot(void) {
    INPUT inputs[6] = { 0 };
    for (int i = 0; i < 6; i++) inputs[i].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LWIN;
    inputs[1].ki.wVk = VK_LSHIFT;
    inputs[2].ki.wVk = 'S';

    inputs[3].ki.wVk = VK_LWIN;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[4].ki.wVk = VK_LSHIFT;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[5].ki.wVk = 'S';
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(6, inputs, sizeof(INPUT));
#ifdef _DEBUG
    print(L"Taking screenshot\n");
#endif
    return;
}
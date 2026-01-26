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


int WINAPI wmain() {

      print(L"mission starto!\n");
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
                                    CreateDesktop( L"Desktop2", NULL, NULL, 0, GENERIC_ALL, NULL );
                                    break;
                              }

                              case 1: {
                                    
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

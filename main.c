/*
* Author: Ikxi
* Date: 24.01.2026
*/

#include "main.h"
#include "monitor.h"
#include "extra.h"


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
      if ( mainWindow == NULL ) { error_exit( L"Couldn't create a main window." ); }

      ShowWindow( mainWindow, SW_HIDE );
#ifdef _DEBUG
      ShowWindow( GetConsoleWindow(), SW_SHOW );
#else
      ShowWindow( GetConsoleWindow(), SW_HIDE );
#endif // _DEBUG

      get_monitors();

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
            case WM_TIMER: {
                  monitorID = 0;
                  get_monitors();
                  return 0;
            }

            case WM_DESTROY: {
                  destroy_monitors();
                  PostQuitMessage( 0 );
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
      return -1;
}

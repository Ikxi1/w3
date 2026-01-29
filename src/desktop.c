#include "../include/desktop.h"


static BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam );


void getOpenWindows() {
      size_t window_count = 0;
      AppList list = { NULL, 0 };
      // EnumWindow( EnumWindowsProc, (LPARAM)&list );
}


static BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam ) {
      AppList* list = (AppList*)lParam;

      if ( !IsWindowVisible( hwnd ) ) return TRUE;
      if ( GetWindow( hwnd, GW_OWNER ) != NULL ) return TRUE;
      return FALSE;
}

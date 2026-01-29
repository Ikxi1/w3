#include "../include/monitor.h"
#include "../include/extra.h"


int compare_monitors( const void *a, const void *b );

int monitorID = 0;
int monitorCount = 0;
MonitorInfo* monitors = NULL;


void get_monitors() {
      print( L"Initializing monitors.\n" );
      monitorCount = GetSystemMetrics( SM_CMONITORS );
      monitors = malloc( sizeof( MonitorInfo ) * monitorCount );
      if ( monitors == NULL ) {
            error_exit( L"Failed to allocate memory for monitors.\n" );
      }
      EnumDisplayMonitors( NULL, NULL, MonitorEnumProc, 0 );

      qsort( monitors, monitorCount, sizeof( MonitorInfo ), compare_monitors );
      for ( int i = 0; i < monitorCount; i++ ) {
            monitors[i].id = i;
      }

#ifdef _DEBUG
      for ( int i = 0; i < monitorCount; i++ ) {
            print( L"Monitor %d: Name=%ls Position=(%d,%d), Size=(%d,%d)\n", monitors[i].id, monitors[i].name,
                   monitors[i].pos.x, monitors[i].pos.y, monitors[i].size.x, monitors[i].size.y );
      }
#endif
      return;
}


void destroy_monitors() {
      print( L"Freeing monitors\n" );
      free( monitors );
}


BOOL CALLBACK MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData ) {
      MONITORINFOEX mi;
      mi.cbSize = sizeof( mi );
      if ( GetMonitorInfo( hMonitor, (LPMONITORINFO)&mi ) ) {
            monitors[monitorID].id = monitorID;
            monitors[monitorID].pos.x = mi.rcMonitor.left;
            monitors[monitorID].pos.y = mi.rcMonitor.top;
            monitors[monitorID].size.x = mi.rcMonitor.right - mi.rcMonitor.left;
            monitors[monitorID].size.y = mi.rcMonitor.bottom - mi.rcMonitor.top;
            wcscpy_s( monitors[monitorID].name, CCHDEVICENAME, mi.szDevice );
            monitorID++;
      }

      return TRUE;
}


int compare_monitors( const void *a, const void *b ) {
      MonitorInfo* ma = (MonitorInfo*)a;
      MonitorInfo* mb = (MonitorInfo*)b;
      return wcscmp( ma->name, mb->name );
}


void switch_to_screen(int screen) {
      if (screen > monitorCount) {
            print(L"Monitor doesn't exist.");
            return;
      }
      screen--;
      int x = monitors[screen].pos.x + monitors[screen].size.x / 2;
      int y = monitors[screen].pos.y + monitors[screen].size.y / 2;
      SetCursorPos(x, y);
}


void move_to_screen(int direction) {

}

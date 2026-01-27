#include "monitor.h"
#include "extra.h"


int compare_monitors( const void *a, const void *b );

int monitorID = 0;
int monitorCount = 0;
MonitorInfo *monitors = NULL;


void get_monitors() {
#ifdef _DEBUG
      print( L"Initializing monitors.\n" );
#endif
      monitorCount = GetSystemMetrics( SM_CMONITORS );
      monitors = malloc( sizeof( MonitorInfo ) * monitorCount );
      if ( monitors == NULL ) { error_exit( L"Failed to allocate memory for monitors.\n" ); return; }
      EnumDisplayMonitors( NULL, NULL, MonitorEnumProc, 0 );

      qsort( monitors, monitorCount, sizeof( MonitorInfo ), compare_monitors );
      for ( int i = 0; i < monitorCount; i++ ) { monitors[ i ].id = i; }

#ifdef _DEBUG
      for ( int i = 0; i < monitorCount; i++ ) {
            print( L"Monitor %d: Name=%ls Position=(%d,%d), Size=(%d,%d)\n",
                   monitors[ i ].id, monitors[ i ].name, monitors[ i ].pos.x, monitors[ i ].pos.y,
                   monitors[ i ].size.x, monitors[ i ].size.y );
      }
#endif
      return;
}


void destroy_monitors() {
#ifdef _DEBUG
      print( L"Freeing monitors\n" );
#endif
      free( monitors );
}


BOOL CALLBACK MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData ) {
      MONITORINFOEX mi;
      mi.cbSize = sizeof( mi );
      if ( GetMonitorInfo( hMonitor, &mi ) ) {
            monitors[ monitorID ].id = monitorID;
            monitors[ monitorID ].pos.x = mi.rcMonitor.left;
            monitors[ monitorID ].pos.y = mi.rcMonitor.top;
            monitors[ monitorID ].size.x = mi.rcMonitor.right - mi.rcMonitor.left;
            monitors[ monitorID ].size.y = mi.rcMonitor.bottom - mi.rcMonitor.top;
            wcscpy_s(monitors[ monitorID ].name, CCHDEVICENAME, mi.szDevice);
            monitorID++;
      }

      return TRUE;
}


int compare_monitors(const void *a, const void *b) {
    MonitorInfo *ma = (MonitorInfo*)a;
    MonitorInfo *mb = (MonitorInfo*)b;
    return wcscmp(ma->name, mb->name);
}

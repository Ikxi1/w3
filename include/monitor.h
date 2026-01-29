#pragma once

#include "main.h"
typedef struct monitorinfo {

      int id;
      Vec2 pos;
      Vec2 size;
      WCHAR name[CCHDEVICENAME];
} MonitorInfo;

extern int monitorID;
extern int monitorCount;
extern MonitorInfo* monitors;

void get_monitors();
void destroy_monitors();
BOOL CALLBACK MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData );

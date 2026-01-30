#include "../include/monitor.h"
#include "../include/extra.h"


int compare_monitors(const void *a, const void *b);

int          monitorID     = 0;
int          monitorCount  = 0;
int          primary_index = 0;
MonitorInfo  primary       = {0};
MonitorInfo *monitors      = NULL;


void get_monitors() {
      print(L"Initializing monitors.\n");
      monitorCount = GetSystemMetrics(SM_CMONITORS);
      monitors = malloc(sizeof(MonitorInfo) * monitorCount);
      MonitorInfo *monitors2 = malloc(sizeof(MonitorInfo) * monitorCount);
      if (monitors == NULL) { error_exit(L"Failed to allocate memory for monitors.\n"); }
      EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);

       /* sort by numbers */
      qsort(monitors, monitorCount, sizeof(MonitorInfo), compare_monitors);
      for (int i = 0; i < monitorCount; i++) {
            monitors[i].id = i;
      }
      for (int i = 0; i < monitorCount; i++) {
            if (monitors[i].pos.x == 0 && monitors[i].pos.y == 0) {
                  // memcpy(&primary, monitors + (i * sizeof(MonitorInfo)), sizeof(MonitorInfo));
                  primary.id = monitors[i].id;
                  wcscpy_s(primary.name, CCHDEVICENAME, monitors[i].name);
                  primary.pos = monitors[i].pos;
                  primary.size = monitors[i].size;
                  primary_index = i;
            }
      }

      /* put primary first */
      memcpy(monitors2, monitors, sizeof(MonitorInfo) * monitorCount);
      if (primary_index != 0) {
            monitors[0] = monitors2[primary_index];
            monitors[primary_index] = monitors2[0];
      }

#ifdef _DEBUG
      for (int i = 0; i < monitorCount; i++) {
            print(L"Monitor %d: Name=%ls Position=(%d,%d), Size=(%d,%d)\n", monitors[i].id, monitors[i].name,
                  monitors[i].pos.x, monitors[i].pos.y, monitors[i].size.x, monitors[i].size.y);
      }
#endif
      free(monitors2);
}


void destroy_monitors() {
      print(L"Freeing monitors\n");
      free(monitors);
}


BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
      MONITORINFOEX mi;
      mi.cbSize = sizeof(mi);
      if (GetMonitorInfo(hMonitor, (LPMONITORINFO)&mi)) {
            monitors[monitorID].id     = monitorID;
            monitors[monitorID].pos.x  = mi.rcMonitor.left;
            monitors[monitorID].pos.y  = mi.rcMonitor.top;
            monitors[monitorID].size.x = mi.rcMonitor.right - mi.rcMonitor.left;
            monitors[monitorID].size.y = mi.rcMonitor.bottom - mi.rcMonitor.top;
            wcscpy_s(monitors[monitorID].name, CCHDEVICENAME, mi.szDevice);
            monitorID++;
            // if (mi.rcMonitor.left == 0 && mi.rcMonitor.top == 0) {
            //       primary.id = monitors[monitorID].id;
            //       wcscpy_s(primary.name, CCHDEVICENAME, monitors[monitorID].name);
            //       primary.pos = monitors[monitorID].pos;
            //       primary.size = monitors[monitorID].size;
            //       primary_index = monitorID;
            // }
      }
      return TRUE;
}


int compare_monitors(const void *a, const void *b) {
      MonitorInfo *ma = (MonitorInfo *)a;
      MonitorInfo *mb = (MonitorInfo *)b;
      return wcscmp(ma->name, mb->name);
}


void switch_to_screen(int screen) {
      if (screen > monitorCount) {
            print(L"Monitor doesn't exist.\n");
            return;
      }
      screen--;
      int x = monitors[screen].pos.x + monitors[screen].size.x / 2;
      int y = monitors[screen].pos.y + monitors[screen].size.y / 2;
      SetCursorPos(x, y);
}


void move_to_screen(enum Direction dir) {
      POINT cursorPos;
      GetCursorPos(&cursorPos);

      int curMonitor = -1;
      for (int i = 0; i < monitorCount; i++) {
            if (cursorPos.x >= monitors[i].pos.x &&
                cursorPos.y >= monitors[i].pos.y &&
                cursorPos.x < monitors[i].pos.x + monitors[i].size.x &&
                cursorPos.y < monitors[i].pos.y + monitors[i].size.y) {
                  curMonitor = i;
                  break;
            }
      }

      if (curMonitor == -1) {
            print(L"Cursor is not on any known monitor.\n");
            return;
      }

      RECT curR  = {
            monitors[curMonitor].pos.x,
            monitors[curMonitor].pos.y,
            monitors[curMonitor].pos.x + monitors[curMonitor].size.x,
            monitors[curMonitor].pos.y + monitors[curMonitor].size.y
      };
      int  curCx = (int)((curR.left + curR.right) / 2.0);
      int  curCy = (int)((curR.top + curR.bottom) / 2.0);

      /* Check if there is a screen when moving the cursor to each direction */
      /* left */
      POINT p     = {0};
      int   tries = 0;
      while (tries < 3) {
            if (dir == Left) {
                  p.x = monitors[curMonitor].pos.x - 1;
                  if (tries == 0) p.y = monitors[curMonitor].pos.y + monitors[curMonitor].size.y;
                  else if (tries == 1) p.y = monitors[curMonitor].pos.y + monitors[curMonitor].size.y / 2;
                  else if (tries == 2) p.y = monitors[curMonitor].pos.y;
            } else if (dir == Up) {
                  if (tries == 0) p.x = monitors[curMonitor].pos.x + monitors[curMonitor].size.x - 1; /* -1 just cause*/
                  else if (tries == 1) p.x = monitors[curMonitor].pos.x + monitors[curMonitor].size.x / 2;
                  else if (tries == 2) p.x = monitors[curMonitor].pos.x;
                  p.y = monitors[curMonitor].pos.y - 1;
            } else if (dir == Right) {
                  p.x = monitors[curMonitor].pos.x + monitors[curMonitor].size.x + 1;
                  if (tries == 0) p.y = monitors[curMonitor].pos.y + monitors[curMonitor].size.y;
                  else if (tries == 1) p.y = monitors[curMonitor].pos.y + monitors[curMonitor].size.y / 2;
                  else if (tries == 2) p.y = monitors[curMonitor].pos.y;
            } else if (dir == Down) {
                  if (tries == 0) p.x = monitors[curMonitor].pos.x + monitors[curMonitor].size.y;
                  else if (tries == 1) p.x = monitors[curMonitor].pos.x + monitors[curMonitor].size.y / 2;
                  else if (tries == 2) p.x = monitors[curMonitor].pos.x;
                  p.y = monitors[curMonitor].pos.y + monitors[curMonitor].size.y + 1;
            }

            for (int i = 0; i < monitorCount; i++) {
                  if (p.x >= monitors[i].pos.x &&
                      p.y >= monitors[i].pos.y &&
                      p.x < monitors[i].pos.x + monitors[i].size.x &&
                      p.y < monitors[i].pos.y + monitors[i].size.y) {
                        SetCursorPos(
                              monitors[i].pos.x + monitors[i].size.x/2,
                              monitors[i].pos.y + monitors[i].size.y/2
                        );
                        return;
                  }
            }
            tries++;
      }
}

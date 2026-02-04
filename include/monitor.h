#pragma once

#include "main.h"


typedef struct monitorinfo {
      int   id;
      Vec2  pos;
      Vec2  size;
      WCHAR name[CCHDEVICENAME];
} MonitorInfo;

extern int          monitorID;
extern int          monitorCount;
extern MonitorInfo *monitors;
extern MonitorInfo  primary;
extern int          primary_index;

enum Direction {
      Left,
      Up,
      Right,
      Down
};

/*
Get all visible/real monitors connected to the PC.
Call this at the beginning of the program.
You can also call it periodically to monitor, if the
number of monitors changes. But free the previous monitors.

Input:
      None

Output:
      None

Modifies:
      monitorID: int
      monitorCount: int
      monitors: MonitorInfo*
 */
void get_monitors();

/*
Frees all allocated monitors.

Input:
      None

Output:
      None

Modifies:
      monitors: MonitorInfo*
 */
void destroy_monitors();

/*
Callback that gets called in 'get_monitors()' iterates
over all monitors and adds their properties to *monitors.

THIS FUNCTION IS NOT TO BE CALLED DIRECTLY.

Input:
      These are all managed by WinAPI

Output:
      This is only for WinAPI

Modifies:
      monitors: MonitorInfo*
 */
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

/*
Moves the mouse cursor to the specified screen.

Input:
      screen: int
            - the index for the monitor, starting at 1
            - does nothing if screen is out of bounds

Output:
      None

Modifies:
      Cursor position
 */
void switch_cursor_to_screen(int screen);

/*
Moves to cursor to a screen in the specified direction.

Input:
      direction: enum Direction
            - the direction to move the cursor in
            - does nothing if there is no monitor
              in the given direction

Output:
      None

Modifies:
      Cursor position
 */
void move_cursor_to_screen(enum Direction dir);

/*
Moves active program to the specified screen.

Input:
      screen: int
            - the index for the monitor, starting at 1
            - does nothing if screen is out of bounds

Output:
      None

Modifies:
      Active program position
      Cursor position
 */
void switch_program_to_screen(int screen);

/*
Moves active program to a screen in the specified direction.

Input:
      direction: enum Direction
            - the direction to move the program in
            - does nothing if there is no monitor
              in the given direction

Output:
      None

Modifies:
      Active program position
      Cursor position
 */
void move_program_to_screen(enum Direction dir);

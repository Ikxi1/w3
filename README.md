# w3

Utility for Windows/Slopdows/Winslop that's supposed to be similar to the i3 window manager on Linux.\

Features:
- Quit: Win+Shift+E
- Move the cursor across your screens: Win+[Number]
- Open Windows menu: Win+D
- Take screenshot: Win+Shift+S (like usual)
- Breaking PowerToys shortcuts that use Win-key

This project is a solution file, so compilation works with Rider and Visual Studio.\
WinAPI is used everywhere, so you NEED Visual Studio (unless you can somehow use Windows.h without VS, idk).\
You can probably just also compile it with whatever else, as long as Windows.h exists. Just gotta make your own script, Makefile, CMake, nob.h.

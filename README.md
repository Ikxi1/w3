# w3

Utility for Windows/Slopdows/Winslop that's supposed to be similar to the i3 window manager on Linux.\

Features:
- Open start menu: Win+D
- Quit: Win+Shift+E
- Open Windows settings: Win+I (like usual)
- Close programs: Win+Shift+Q (Alt+F4 still works)
- Take screenshot: Win+Shift+S (like usual)
- Switch screens: Win+[Number]
- Move the cursor across screens: Win+[Arrow key]
- Breaking PowerToys shortcuts that use Win-key (or any other shortcut/program relying on that key)

This project is a solution file, so compilation works with Rider and Visual Studio.\
WinAPI is used everywhere, so you NEED Visual Studio (unless you can somehow use Windows.h without VS, idk).\
You can probably just also compile it with whatever else, as long as Windows.h exists. Just gotta make your own script, Makefile, CMake, nob.h.

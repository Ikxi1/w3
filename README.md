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

## Testing

A comprehensive test suite is available in the `tests/` directory. The tests use the Unity testing framework and cover:
- Monitor management and comparison functions
- Keyboard event handling and state management
- Shortcut key combinations and input structures
- Window enumeration logic
- Core utility functions and data structures

To run the tests on Windows:

**Using Make (MinGW):**
```bash
cd tests
make test
```

**Using PowerShell:**
```powershell
cd tests
.\run_tests.ps1
```

**Using Batch Script:**
```cmd
cd tests
run_tests.bat
```

**Using CMake:**
```bash
cd tests
mkdir build
cd build
cmake ..
cmake --build .
ctest --output-on-failure
```

See `tests/README.md` for detailed information about the test suite, including what is tested and how to add new tests.

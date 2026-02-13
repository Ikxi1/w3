@echo off
REM Build and run all tests for w3 project
REM This script is for Windows with MinGW installed

echo ============================================
echo Building and Running w3 Test Suite
echo ============================================
echo.

REM Check if make is available
where make >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: make not found. Please install MinGW or add it to PATH.
    exit /b 1
)

REM Check if gcc is available
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: gcc not found. Please install MinGW or add it to PATH.
    exit /b 1
)

echo Build tools found.
echo.

REM Clean previous builds
echo Cleaning previous builds...
make clean
echo.

REM Build all tests
echo Building tests...
make all
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Error: Build failed!
    exit /b 1
)
echo.

REM Run all tests
echo Running tests...
echo.
make test
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Error: Some tests failed!
    exit /b 1
)

echo.
echo ============================================
echo All tests completed successfully!
echo ============================================
exit /b 0

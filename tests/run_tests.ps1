# PowerShell script to build and run w3 tests
# Requires MinGW or similar toolchain with make and gcc

Write-Host "============================================" -ForegroundColor Cyan
Write-Host "Building and Running w3 Test Suite" -ForegroundColor Cyan
Write-Host "============================================" -ForegroundColor Cyan
Write-Host ""

# Check if make is available
$makeCmd = Get-Command make -ErrorAction SilentlyContinue
if (-not $makeCmd) {
    Write-Host "Error: make not found. Please install MinGW or add it to PATH." -ForegroundColor Red
    exit 1
}

# Check if gcc is available
$gccCmd = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gccCmd) {
    Write-Host "Error: gcc not found. Please install MinGW or add it to PATH." -ForegroundColor Red
    exit 1
}

Write-Host "Build tools found." -ForegroundColor Green
Write-Host ""

# Navigate to tests directory
$scriptPath = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $scriptPath

# Clean previous builds
Write-Host "Cleaning previous builds..." -ForegroundColor Yellow
& make clean
Write-Host ""

# Build all tests
Write-Host "Building tests..." -ForegroundColor Yellow
& make all
if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Error: Build failed!" -ForegroundColor Red
    exit 1
}
Write-Host ""

# Run all tests
Write-Host "Running tests..." -ForegroundColor Yellow
Write-Host ""
& make test
if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Error: Some tests failed!" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "============================================" -ForegroundColor Cyan
Write-Host "All tests completed successfully!" -ForegroundColor Green
Write-Host "============================================" -ForegroundColor Cyan
exit 0

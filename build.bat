@echo off
setlocal enabledelayedexpansion

REM Add Qt and MinGW to PATH
set PATH=C:\Qt\6.11.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%

REM Run qmake and mingw32-make
cd /d "d:\Minecraft Bedrock\Easy Bedrock Server\minecraftbedrockconsole"
del /f /q Makefile* ui_*.h 2>nul
qmake BedrockConsole.pro -spec win32-g++
if %errorlevel% neq 0 (
    echo qmake failed
    exit /b %errorlevel%
)

mingw32-make release
if %errorlevel% neq 0 (
    echo Build failed
    exit /b %errorlevel%
)

REM Ensure dist directory exists and copy fresh exe
if not exist dist mkdir dist
copy /Y release\BedrockConsole.exe dist\BedrockConsole.exe
if %errorlevel% neq 0 (
    echo Warning: Failed to copy exe to dist
)

echo Build complete. Exe updated in dist\
exit /b 0

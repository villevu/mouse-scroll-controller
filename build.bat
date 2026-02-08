@echo off
echo Compiling Mouse Scroll Controller (C++ Win32)...

REM Compile resource file
rc disableScrollWheel.rc

REM Compile and link with full optimizations
cl /EHsc /O2 /MT /W3 /DUNICODE /D_UNICODE /GL disableScrollWheel.cpp disableScrollWheel.res /link /SUBSYSTEM:WINDOWS /LTCG user32.lib gdi32.lib shell32.lib comctl32.lib /OUT:disableScrollWheel.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Output: disableScrollWheel_native.exe
    echo File size:
    dir disableScrollWheel_native.exe | find "disableScrollWheel_native.exe"
) else (
    echo.
    echo Build failed!
)

pause

@echo off
echo Compiling Mouse Scroll Controller (C++ Win32)...

REM Initialize Visual Studio environment if not already set
if not defined VCINSTALLDIR (
    echo Setting up Visual Studio environment...
    
    REM Try VS 2022 first
    if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    ) else (
        echo ERROR: Could not find Visual Studio installation.
        echo Please run this from a "Developer Command Prompt for VS" or install Visual Studio Build Tools.
        pause
        exit /b 1
    )
)

REM Compile resource file
rc disableScrollWheel.rc

REM Compile and link with full optimizations
cl /EHsc /O2 /MT /W3 /DUNICODE /D_UNICODE /GL disableScrollWheel.cpp disableScrollWheel.res /link /SUBSYSTEM:WINDOWS /LTCG user32.lib gdi32.lib shell32.lib comctl32.lib /OUT:disableScrollWheel.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Output: disableScrollWheel.exe
    echo File size:
    dir disableScrollWheel.exe | find "disableScrollWheel.exe"
) else (
    echo.
    echo Build failed!
)

pause

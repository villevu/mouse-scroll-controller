# Mouse Scroll Controller

A lightweight Windows utility to temporarily disable your mouse scroll wheel. Useful for faulty mice that scroll randomly.

![Platform](https://img.shields.io/badge/platform-Windows%207%2B-lightgrey) ![License](https://img.shields.io/badge/license-MIT-green) ![Size](https://img.shields.io/badge/size-lightweight-blue)

## Download

**[Latest Release](../../releases/latest)** - Standalone executable, no dependencies

## Features

- 🖱️ Toggle scroll wheel on/off
- ⌨️ Global hotkey (Ctrl+Shift+S)
- 🚀 Works on Windows 7, 8, 10, 11

1. Download `disableScrollWheel.exe`
2. Run it
3. Click "Disable Scrolling" or press **Ctrl+Shift+S**

## Building from Source

### Prerequisites
- Visual Studio 2022 (or Build Tools)
- Windows SDK

### Build
Simply run from any command prompt:
```cmd
cd path/to/project
build.bat
```

The build script automatically detects and initializes the Visual Studio environment.

## Anticheat & Online Gaming Warning ⚠️

**Important:** This utility uses a **Low-Level Mouse Hook** (`WH_MOUSE_LL`) to intercept input. Because this is the same method used by some macro scripts and cheat tools, it may interact poorly with modern anticheat systems (such as **Vanguard, EAC, or BattlEye**).

* **Risk of Bans:** While the tool is not a "cheat," some aggressive anticheat engines may flag any third-party software that intercepts raw mouse input.
* **Input Blocking:** The tool may be automatically ignored or disabled by Windows when a protected game window is active.
* **Recommended Action:** It is highly recommended to **exit this tool before launching online multiplayer games** to avoid any potential account flags or game crashes.

> **Use at your own risk in gaming environments.**

## Antivirus False Positives ⚠️

**This tool is safe and open source.** Some antivirus programs might still flag it because it uses low-level mouse hooks (a Windows API that malware sometimes abuses).

**What you can do:**
- ✅ Review the source code (it's only ~250 lines)
- ✅ Compile it yourself
- ✅ Add an exception in your antivirus

### How It Works
Uses Windows `SetWindowsHookEx` API with `WH_MOUSE_LL` hook to intercept and suppress scroll wheel events (`WM_MOUSEWHEEL`). All other mouse functionality remains normal. No network access, no file access, no data collection.

## Distribution

The repository contains:
- The `.exe` file
- Source code (for verification)

## License

MIT License - See [LICENSE](LICENSE)

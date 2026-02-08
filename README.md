# Mouse Scroll Controller

A lightweight Windows utility to temporarily disable your mouse scroll wheel. Useful for faulty mice that scroll randomly.

![Size](https://img.shields.io/badge/size-129%20KB-blue) ![Platform](https://img.shields.io/badge/platform-Windows%207%2B-lightgrey) ![License](https://img.shields.io/badge/license-MIT-green)

## Download

**[Latest Release](../../releases/latest)** - Single 129 KB executable, zero dependencies

## Features

- 🖱️ Toggle scroll wheel on/off
- ⌨️ Global hotkey (Ctrl+Shift+S)
- 🚀 Works on Windows 7, 8, 10, 11

1. Download `disableScrollWheel_native.exe`
2. Run it
3. Click "Disable Scrolling" or press **Ctrl+Shift+S**

## Building from Source

### Prerequisites
- Visual Studio 2022 (or Build Tools)
- Windows SDK

### Build
Open **Developer Command Prompt for VS 2022**:
```cmd
cd path/to/project
build.bat
```

## Antivirus False Positives ⚠️

**This tool is safe and open source.** Some antivirus programs flag it because it uses low-level mouse hooks (a Windows API that malware sometimes abuses).

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

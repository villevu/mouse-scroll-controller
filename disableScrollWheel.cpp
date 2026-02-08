#include <windows.h>
#include <commctrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

// Global variables
HINSTANCE g_hInst = NULL;
HWND g_hMainWnd = NULL;
HWND g_hStatusLabel = NULL;
HWND g_hToggleButton = NULL;
HWND g_hHotkeyLabel = NULL;
HHOOK g_hMouseHook = NULL;
bool g_bScrollDisabled = false;

// Constants
#define ID_TOGGLE_BUTTON 1001
#define HOTKEY_ID 1

// Forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProcessInputData(int, WPARAM, LPARAM);
void ToggleScrolling();
void EnableScrolling();
void DisableScrolling();
void UpdateUI();

// Input processing callback
LRESULT CALLBACK ProcessInputData(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        // Check if it's a mouse wheel event
        if (wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL)
        {
            // Suppress the scroll event
            return 1;
        }
    }
    
    return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

void ToggleScrolling()
{
    if (g_bScrollDisabled)
        EnableScrolling();
    else
        DisableScrolling();
}

void DisableScrolling()
{
    if (g_hMouseHook == NULL)
    {
        g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, ProcessInputData, g_hInst, 0);
        
        if (g_hMouseHook != NULL)
        {
            g_bScrollDisabled = true;
            UpdateUI();
        }
        else
        {
            MessageBox(g_hMainWnd, L"Failed to disable scrolling. Try running as Administrator.", 
                      L"Error", MB_OK | MB_ICONERROR);
        }
    }
}

void EnableScrolling()
{
    if (g_hMouseHook != NULL)
    {
        UnhookWindowsHookEx(g_hMouseHook);
        g_hMouseHook = NULL;
        g_bScrollDisabled = false;
        UpdateUI();
    }
}

void UpdateUI()
{
    if (g_bScrollDisabled)
    {
        SetWindowText(g_hStatusLabel, L"Scroll Wheel: DISABLED");
        SetWindowText(g_hToggleButton, L"Enable Scrolling");
    }
    else
    {
        SetWindowText(g_hStatusLabel, L"Scroll Wheel: ENABLED");
        SetWindowText(g_hToggleButton, L"Disable Scrolling");
    }
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Create status label (no background panel)
        g_hStatusLabel = CreateWindowEx(
            0,
            L"STATIC",
            L"Scroll Wheel: ENABLED",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            20, 30, 280, 30,
            hWnd, NULL, g_hInst, NULL
        );
        
        // Set font for status label
        HFONT hFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
        SendMessage(g_hStatusLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
        
        // Create toggle button
        g_hToggleButton = CreateWindowEx(
            0,
            L"BUTTON",
            L"Disable Scrolling",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            70, 75, 180, 40,
            hWnd, (HMENU)ID_TOGGLE_BUTTON, g_hInst, NULL
        );
        
        HFONT hButtonFont = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                       DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
        SendMessage(g_hToggleButton, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
        
        // Create hotkey label
        g_hHotkeyLabel = CreateWindowEx(
            0,
            L"STATIC",
            L"Hotkey: Ctrl+Shift+S to toggle",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            20, 125, 280, 20,
            hWnd, NULL, g_hInst, NULL
        );
        
        HFONT hSmallFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
        SendMessage(g_hHotkeyLabel, WM_SETFONT, (WPARAM)hSmallFont, TRUE);
        
        // Register hotkey (Ctrl+Shift+S)
        RegisterHotKey(hWnd, HOTKEY_ID, MOD_CONTROL | MOD_SHIFT, 'S');
        
        // Don't auto-start hook - wait for user action
        // This reduces AV false positives
        
        break;
    }
    
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_TOGGLE_BUTTON)
        {
            ToggleScrolling();
        }
        break;
    
    case WM_HOTKEY:
        if (wParam == HOTKEY_ID)
        {
            ToggleScrolling();
        }
        break;
    

    
    case WM_CLOSE:
        // Cleanup and exit
        if (g_hMouseHook != NULL)
        {
            UnhookWindowsHookEx(g_hMouseHook);
            g_hMouseHook = NULL;
        }
        UnregisterHotKey(hWnd, HOTKEY_ID);
        DestroyWindow(hWnd);
        break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    g_hInst = hInstance;
    
    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&icex);
    
    // Register window class
    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszClassName = L"MouseScrollController";
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create window
    g_hMainWnd = CreateWindowEx(
        0,
        L"MouseScrollController",
        L"Mouse Scroll Controller",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 340, 200,
        NULL, NULL, hInstance, NULL
    );
    
    if (!g_hMainWnd)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    ShowWindow(g_hMainWnd, nCmdShow);
    UpdateWindow(g_hMainWnd);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}

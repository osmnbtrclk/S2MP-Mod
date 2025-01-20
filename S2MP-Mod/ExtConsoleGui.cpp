#include "pch.h"
#include <windows.h>
#include "resource.h"
#include <stdio.h>
#include <string>
#include <locale>
#include <thread>
#include <chrono>
#include "ExtConsoleGui.h"
#include "Console.h"
#include "ConfigManager.h"
//#include <iostream> //for debugging
const char g_szClassName[] = "myWindowClass";
static HWND txtbox_output;
static HWND chkbox_darkmode;
bool isReady = false;
bool startInDarkMode = false;
std::string filename = "s2mp-mod.cfg";
std::string key = "extConDark";

bool ExternalConsoleGui::isExtConGuiReady() {
    return isReady;
}

// Helper function to convert std::string to std::wstring
std::wstring stringToWString(const std::string& str) {
    // Check if the input string is empty
    if (str.empty()) {
        return std::wstring();
    }

    // Calculate the number of wide characters to be allocated
    int wchars_num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

    // Allocate the wide string
    std::wstring wstr(wchars_num, 0);

    // Convert from UTF-8 to wide string
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], wchars_num);

    // Remove the extra null terminator
    wstr.pop_back();

    return wstr;
}

void ExternalConsoleGui::print(const std::string& s) {
    //std::cout << "ExternalConsoleGui::print :" << s << std::endl;
    std::string modifiedString = s + "\r\n";
    // Convert std::string (with newline) to std::wstring
    std::wstring wstrNewText = stringToWString(modifiedString);
    // Check current text length and clear if necessary
    int length = GetWindowTextLength(txtbox_output);
    if (length + wstrNewText.size() > 30000) {
        SetWindowText(txtbox_output, L""); // Clear the text box
        length = 0;
    }
    wchar_t* buffer = new wchar_t[length + wstrNewText.size() + 1]; // +1 for null terminator
    GetWindowText(txtbox_output, buffer, length + 1); // +1 to include null terminator in the copy
    wcscat_s(buffer, length + wstrNewText.size() + 1, wstrNewText.c_str());
    SetWindowText(txtbox_output, buffer);
    delete[] buffer;

    // Move the caret to the end of the text
    int textLength = GetWindowTextLength(txtbox_output);
    SendMessage(txtbox_output, EM_SETSEL, (WPARAM)textLength, (LPARAM)textLength);
    // Scroll to the caret position
    SendMessage(txtbox_output, EM_SCROLLCARET, 0, 0);
    InvalidateRect(txtbox_output, NULL, TRUE);
}

void sendToConsole(HWND hwndEdit) {
    wchar_t buffer[1024]; // Buffer for text
    GetWindowText(hwndEdit, buffer, sizeof(buffer) / sizeof(wchar_t)); // Get text from edit control
    std::wstring wstr(buffer);

    // Calculate the size needed for the new string
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(size_needed, 0);
    // Perform the actual conversion
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &str[0], size_needed, NULL, NULL);

    Console::execCmd(str);
    ExternalConsoleGui::print(str);
    SetWindowText(hwndEdit, L""); // Clear the edit control
}

// Global variable to store original edit control procedure
WNDPROC g_wpOrigEditProc;

// Subclass procedure for intercepting events from the edit control
LRESULT CALLBACK EditSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CHAR:
        if (wParam == VK_RETURN) // Check if the key is Enter
        {
            sendToConsole(hwnd);
            return 0; // Prevent beeping sound
        }
        break;
    }
    return CallWindowProc(g_wpOrigEditProc, hwnd, msg, wParam, lParam);
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND txtbox_input;
    // Handle to the edit control
    static HWND hwndImage; // Handle for the image control
    static HFONT hFont;    // Handle for the font

    switch (msg)
    {
    case WM_CREATE:
    {

        // Create the checkbox for dark mode
        chkbox_darkmode = CreateWindowEx(
            0, // Extended styles
            L"BUTTON", // Class name for a button which can be used for checkboxes
            L"Dark Mode", // Button text
            WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, // Styles (make it visible, child, and a checkbox)
            15, 535, // Position (x, y) - adjust this to put it at the bottom
            100, 20, // Size (width, height)
            hwnd, // Parent window
            (HMENU)3, // Menu handle or child ID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // Instance handle
            NULL); // Additional application data

        if (startInDarkMode) {
            SendMessage(chkbox_darkmode, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
        }

        hwndImage = CreateWindowEx(0, L"STATIC", NULL,
            WS_CHILD | WS_VISIBLE | SS_BITMAP,
            0, 0, 731, 100, // Position and size of the image
            hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        //HBITMAP hBitmap = (HBITMAP)::LoadImage(GetModuleHandle(L"t6sp-mod.dll"), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_SHARED);
        HBITMAP hBitmap = LoadBitmap(GetModuleHandle(L"S2MP-Mod.dll"), MAKEINTRESOURCE(IDB_BITMAP1));
        if (hBitmap == NULL) {
            //std::cout << GetLastError() << std::endl;
            MessageBox(hwnd, L"Could not load external console head (Visual Only)", L"Error", MB_OK | MB_ICONEXCLAMATION);
        }
        SendMessage(hwndImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

        txtbox_output = CreateWindowEx(
            NULL, // Extended window styles.
            L"EDIT",          // Class name for edit controls.
            L"",              // Default text.
            WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL, // Window styles. //ES_READONLY disabled until find style fix
            15, 110,          // Position (x, y).
            700, 200,         // Size (width, height).
            hwnd,             // Parent window.
            (HMENU)1,         // Control ID.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // Instance handle.
            NULL);
        if (startInDarkMode) {
            SetBkColor(GetDC(txtbox_output), RGB(71, 71, 71)); // Set background color to dark grey for txtbox_output
            SetTextColor(GetDC(txtbox_output), RGB(255, 255, 255)); // Set text color to white in dark mode
        }
        hFont = CreateFont(
            14, 0, 0, 0, FW_NORMAL,
            FALSE, FALSE, 0, ANSI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, L"Consolas");

        SendMessage(txtbox_output, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(chkbox_darkmode, WM_SETFONT, (WPARAM)hFont, TRUE);

        txtbox_input = CreateWindowEx(
            NULL,
            L"EDIT",
            L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT,
            15, 515, // Position
            700, 20, // Size
            hwnd,
            (HMENU)2,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);
        SendMessage(txtbox_input, WM_SETFONT, (WPARAM)hFont, TRUE);
        if (startInDarkMode) {
            SetBkColor(GetDC(txtbox_input), RGB(71, 71, 71)); // Set background color to dark grey for txtbox_output
            SetTextColor(GetDC(txtbox_input), RGB(255, 255, 255)); // Set text color to white in dark mode
        }

        // Subclass the input textbox
        g_wpOrigEditProc = (WNDPROC)SetWindowLongPtr(txtbox_input, GWLP_WNDPROC, (LONG_PTR)EditSubclassProc);

    }
    break;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        MoveWindow(txtbox_output, 15, 110, width - 30, 400, TRUE);
    }
    break;
    case WM_CTLCOLORBTN:
    {

        HDC hdc = (HDC)wParam;
        HWND hButton = (HWND)lParam;
        if (hButton == chkbox_darkmode)
        {
            LRESULT checkState = SendMessage(chkbox_darkmode, BM_GETCHECK, 0, 0);
            if (checkState == BST_CHECKED)
            {
                SetTextColor(hdc, RGB(255, 255, 255)); // Set text color to white in dark mode
                SetBkColor(hdc, RGB(41, 41, 41)); // Set background color to dark
                static HBRUSH hbrBackground = CreateSolidBrush(RGB(41, 41, 41));
                return (INT_PTR)hbrBackground;
            }
            else
            {
                SetTextColor(hdc, RGB(0, 0, 0)); // Set text color to black in light mode
                SetBkColor(hdc, RGB(240, 240, 240)); // Set background color to light
                static HBRUSH hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
                return (INT_PTR)hbrBackground;
            }
        }
        break;
    }
    case WM_CTLCOLORSTATIC: {
        HDC hdc = (HDC)wParam;
        HWND hButton = (HWND)lParam;
        LRESULT checkState = SendMessage(chkbox_darkmode, BM_GETCHECK, 0, 0);
        if (checkState == BST_CHECKED)
        {

            if (hButton == chkbox_darkmode) {
                SetTextColor(hdc, RGB(255, 255, 255)); // Set text color to white in dark mode
                SetBkColor(hdc, RGB(41, 41, 41)); // Set background color to dark
                static HBRUSH hbrBackground = CreateSolidBrush(RGB(41, 41, 41));
                return (INT_PTR)hbrBackground;
            }
        }
        else
        {
            if (hButton == chkbox_darkmode) {
                SetTextColor(hdc, RGB(0, 0, 0)); // Set text color to black in light mode
                SetBkColor(hdc, RGB(240, 240, 240)); // Set background color to light
                static HBRUSH hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
                return (INT_PTR)hbrBackground;
            }
        }
    }
    case WM_CTLCOLOREDIT:
    {
        HDC hdcEdit = (HDC)wParam;
        HWND hwndEdit = (HWND)lParam;
        LRESULT checkState = SendMessage(chkbox_darkmode, BM_GETCHECK, 0, 0);

        // Create solid brushes outside if conditions if they are used in both.
        static HBRUSH hbrBackgroundDark = CreateSolidBrush(RGB(71, 71, 71)); // Dark mode background brush
        static HBRUSH hbrBackgroundLight = CreateSolidBrush(RGB(255, 255, 255)); // Light mode background brush

        if (checkState == BST_CHECKED) // Dark mode
        {
            SetTextColor(hdcEdit, RGB(255, 255, 255)); // Set text color to white in dark mode
            //SetBkMode(hdcEdit, TRANSPARENT);

            if (hwndEdit == txtbox_output) {
                SetBkColor(hdcEdit, RGB(71, 71, 71)); // Set background color to dark grey for txtbox_output
                SetTextColor(hdcEdit, RGB(255, 255, 255)); // Set text color to white in dark mode
                return (INT_PTR)hbrBackgroundDark;
            }
            else if (hwndEdit == txtbox_input) {
                SetBkColor(hdcEdit, RGB(71, 71, 71)); // Also set for txtbox_input if necessary
                return (INT_PTR)hbrBackgroundDark;
            }
        }
        else // Light mode
        {
            SetTextColor(hdcEdit, RGB(0, 0, 0)); // Set text color to black in light mode
            //SetBkMode(hdcEdit, TRANSPARENT); 

            if (hwndEdit == txtbox_output) {
                SetBkColor(hdcEdit, RGB(255, 255, 255)); // Set background color to white for txtbox_output
                return (INT_PTR)hbrBackgroundLight;
            }
            else if (hwndEdit == txtbox_input) {
                SetBkColor(hdcEdit, RGB(255, 255, 255)); // Also set for txtbox_input if necessary
                return (INT_PTR)hbrBackgroundLight;
            }
        }

        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        // Parse the menu selections:
        switch (wmId)
        {
        case 3: // This is the ID for the dark mode checkbox
            if (wmEvent == BN_CLICKED)
            {
                // Check the state of the checkbox
                LRESULT state = SendMessage(chkbox_darkmode, BM_GETCHECK, 0, 0);
                if (state == BST_CHECKED)
                {
                    // Change the window background color to dark
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(41, 41, 41)));
                    ConfigManager::writeConfigValue(filename, key, true);
                }
                else
                {
                    // Change the window background color to light
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(240, 240, 240)));
                    ConfigManager::writeConfigValue(filename, key, false);
                }
                // Force the window to repaint with the new background color
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }
            break;
        }
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int ExternalConsoleGui::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    if (ConfigManager::configExists(filename)) {
        startInDarkMode = ConfigManager::readConfigValue(filename, key);
    }
    else { //cfg file doesnt exist so store default value
        ConfigManager::writeConfigValue(filename, key, startInDarkMode);
    }

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    HICON hIcon = LoadIcon(GetModuleHandle(L"S2MP-Mod.dll"), MAKEINTRESOURCE(IDB_BITMAP1));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    //wc.hbrBackground;
    if (startInDarkMode) {
        wc.hbrBackground = CreateSolidBrush(RGB(41, 41, 41));
    }
    else {
        wc.hbrBackground = CreateSolidBrush(RGB(240, 240, 240)); //Light mode background color
    }
    wc.lpszMenuName = NULL;
    wc.lpszClassName = (LPCWSTR)g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);




    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Calculating the correct window size for the image
    RECT rect = { 0, 0, 725, 235 }; // Desired client area size
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE); // Adjust according to the window style

    // Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        (LPCWSTR)g_szClassName,
        L"S2MP-Mod External Console",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,  // Adjusted width
        rect.bottom - rect.top + 320,  // Adjusted height for other controls and margins
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }



    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    isReady = true;
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}



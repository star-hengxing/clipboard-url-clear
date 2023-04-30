#include <Windows.h>

#include "clipboard.hpp"

LRESULT CALLBACK ClipWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    static BOOL bListening = FALSE;

    switch (uMsg)
    {
    case WM_CREATE:
        bListening = AddClipboardFormatListener(hWnd);
        return bListening ? 0 : -1;
    case WM_DESTROY:
        if (bListening)
        {
            RemoveClipboardFormatListener(hWnd);
            bListening = FALSE;
        }
        return 0;
    case WM_CLIPBOARDUPDATE:
        clipboard_handle();
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main()
{
    WNDCLASSEX wndClass = {sizeof(WNDCLASSEX)};
    wndClass.lpfnWndProc = ClipWndProc;
    wndClass.lpszClassName = L"ClipWnd";

    if (!RegisterClassEx(&wndClass))
    {
        return -1;
    }

    HWND hWnd = CreateWindowEx(0, wndClass.lpszClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, GetModuleHandle(nullptr), nullptr);

    if (!hWnd)
    {
        return -1;
    }

    MSG msg;
    while (BOOL bRet = GetMessage(&msg, 0, 0, 0))
    {
        if (bRet == -1)
            return -1;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/**
 * Copyright (c) 2019 Noah Johnson
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <stddef.h>

#include <nezumi/window.h>
#include <nezumi/window/window.internal.h>

#include <windows.h>

/* The name of the window class. */
#define WINDOW_CLASS_NAME "main"

/* The style of the window. */
static DWORD style;

/* The main window procedure callback. */
static LRESULT CALLBACK window_procedure(HWND wnd, UINT msg, WPARAM wp,
                                         LPARAM lp)
{
    switch (msg)
    {
        /* The close button was pressed. */
        case WM_CLOSE:
        {
            PostQuitMessage(0);

            return 0;
        }

        /* The size was changed. */
        case WM_SIZE:
        {
            g_nez_window_width = LOWORD(lp);
            g_nez_window_height = HIWORD(lp);

            return 0;
        }

        /* The position was changed. */
        case WM_MOVE:
        {
            g_nez_window_x = (short)(LOWORD(lp));
            g_nez_window_y = (short)(HIWORD(lp));

            return 0;
        }

        /* The focus was changed. */
        case WM_ACTIVATEAPP:
        {
            g_nez_window_focus = wp;

            return 0;
        }
    }

    /* Let Windows handle everything else. */
    return DefWindowProcA(wnd, msg, wp, lp);
}

nez_b32_t nez_window_init(const char *title, int width, int height)
{
    HINSTANCE instance;
    RECT area;
    WNDCLASSA class;

    /* Get Application Instance */
    instance = GetModuleHandleA(NULL);

    /* Get Window Style */
    style = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

    /* Get Window Area */
    area.left   = 0;
    area.top    = 0;
    area.right  = width;
    area.bottom = height;

    AdjustWindowRect(&area, style, NEZ_FALSE);

    /* Register Window Class */
    class.style         = CS_HREDRAW | CS_VREDRAW;
    class.lpfnWndProc   = window_procedure;
    class.cbClsExtra    = 0;
    class.cbWndExtra    = 0;
    class.hInstance     = instance;
    class.hIcon         = LoadIconA(NULL, IDI_APPLICATION);
    class.hCursor       = LoadCursorA(NULL, IDC_ARROW);
    class.hbrBackground = NULL;
    class.lpszMenuName  = NULL;
    class.lpszClassName = WINDOW_CLASS_NAME;

    if (!RegisterClassA(&class))
        return NEZ_FALSE;

    /* Create Window */
    g_nez_window_handle = CreateWindowExA
    (
        0,
        WINDOW_CLASS_NAME,
        title,
        style,
        0,
        0,
        area.right - area.left,
        area.bottom - area.top,
        NULL,
        NULL,
        instance,
        NULL
    );

    if (!g_nez_window_handle)
        return NEZ_FALSE;

    /* Center Window */
    g_nez_window_width = width;
    g_nez_window_height = height;

    nez_window_center();

    /* Success */
    return NEZ_TRUE;
}

nez_b32_t nez_window_events(void)
{
    MSG msg;

    /* Message Loop */
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
    {
        /* The close button was pressed. */
        if (msg.message == WM_QUIT)
            return NEZ_FALSE;

        /* Translate and dispatch the message. */
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return NEZ_TRUE;
}

void nez_window_center(void)
{
    SetWindowPos
    (
        g_nez_window_handle,
        HWND_TOP,
        (GetSystemMetrics(SM_CXSCREEN) - g_nez_window_width) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - g_nez_window_height) / 2,
        0,
        0,
        SWP_NOSIZE
    );
}

void nez_window_set_title(const char *title)
{
    SetWindowTextA(g_nez_window_handle, title);
}

void nez_window_set_size(int width, int height)
{
    RECT area;

    /* Get Window Area */
    area.left   = 0;
    area.top    = 0;
    area.right  = width;
    area.bottom = height;

    AdjustWindowRect(&area, style, NEZ_FALSE);

    /* Set Window Size */
    SetWindowPos
    (
        g_nez_window_handle,
        HWND_TOP,
        0,
        0,
        area.right - area.left,
        area.bottom - area.top,
        SWP_NOMOVE
    );
}

void nez_window_set_position(int x, int y)
{
    SetWindowPos
    (
        g_nez_window_handle,
        HWND_TOP,
        x,
        y,
        0,
        0,
        SWP_NOSIZE
    );
}

void nez_window_set_visible(nez_b32_t visible)
{
    ShowWindow(g_nez_window_handle, visible ? SW_SHOW : SW_HIDE);
}

void nez_window_set_fullscreen(nez_b32_t fullscreen, nez_b32_t borderless)
{
    /* TODO: Add Fullscreen Support */
}
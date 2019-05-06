/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2018 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#ifndef SDL_windowsvideo_h_
#define SDL_windowsvideo_h_

#include "../../core/windows/SDL_windows.h"

#include "../SDL_sysvideo.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1500)
#include <msctf.h>
#else
#include "SDL_msctf.h"
#endif

#include <imm.h>

#define MAX_CANDLIST    10
#define MAX_CANDLENGTH  256

#include "SDL_windowsclipboard.h"
#include "SDL_windowsevents.h"
#include "SDL_windowskeyboard.h"
#include "SDL_windowsmodes.h"
#include "SDL_windowsmouse.h"
#include "SDL_windowsopengl.h"
#include "SDL_windowsopengles.h"
#include "SDL_windowswindow.h"
#include "SDL_events.h"
#include "SDL_loadso.h"


#if WINVER < 0x0601
/* Touch input definitions */
#define TWF_FINETOUCH   1
#define TWF_WANTPALM    2

#define TOUCHEVENTF_MOVE 0x0001
#define TOUCHEVENTF_DOWN 0x0002
#define TOUCHEVENTF_UP   0x0004

DECLARE_HANDLE(HTOUCHINPUT);

typedef struct _TOUCHINPUT {
    LONG      x;
    LONG      y;
    HANDLE    hSource;
    DWORD     dwID;
    DWORD     dwFlags;
    DWORD     dwMask;
    DWORD     dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD     cxContact;
    DWORD     cyContact;
} TOUCHINPUT, *PTOUCHINPUT;

#endif /* WINVER < 0x0601 */

#if WINVER < 0x0603

typedef enum MONITOR_DPI_TYPE {
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

#endif /* WINVER < 0x0603 */

typedef nez_b32_t  (*PFNSHFullScreen)(HWND, DWORD);
typedef void  (*PFCoordTransform)(SDL_Window*, POINT*);

typedef struct
{
    void **lpVtbl;
    int refcount;
    void *data;
} TSFSink;

/* Definition from Win98DDK version of IMM.H */
typedef struct tagINPUTCONTEXT2 {
    HWND hWnd;
    nez_b32_t fOpen;
    POINT ptStatusWndPos;
    POINT ptSoftKbdPos;
    DWORD fdwConversion;
    DWORD fdwSentence;
    union {
        LOGFONTA A;
        LOGFONTW W;
    } lfFont;
    COMPOSITIONFORM cfCompForm;
    CANDIDATEFORM cfCandForm[4];
    HIMCC hCompStr;
    HIMCC hCandInfo;
    HIMCC hGuideLine;
    HIMCC hPrivate;
    DWORD dwNumMsgBuf;
    HIMCC hMsgBuf;
    DWORD fdwInit;
    DWORD dwReserve[3];
} INPUTCONTEXT2, *PINPUTCONTEXT2, NEAR *NPINPUTCONTEXT2, FAR *LPINPUTCONTEXT2;

/* Private display data */

typedef struct SDL_VideoData
{
    int render;

    DWORD clipboard_count;

    /* Touch input functions */
    void* userDLL;
    nez_b32_t (WINAPI *CloseTouchInputHandle)( HTOUCHINPUT );
    nez_b32_t (WINAPI *GetTouchInputInfo)( HTOUCHINPUT, UINT, PTOUCHINPUT, int );
    nez_b32_t (WINAPI *RegisterTouchWindow)( HWND, ULONG );

    void* shcoreDLL;
    HRESULT (WINAPI *GetDpiForMonitor)( HMONITOR         hmonitor,
                                        MONITOR_DPI_TYPE dpiType,
                                        UINT             *dpiX,
                                        UINT             *dpiY );
    
    SDL_nez_b32_t ime_com_initialized;
    struct ITfThreadMgr *ime_threadmgr;
    SDL_nez_b32_t ime_initialized;
    SDL_nez_b32_t ime_enabled;
    SDL_nez_b32_t ime_available;
    HWND ime_hwnd_main;
    HWND ime_hwnd_current;
    HIMC ime_himc;

    WCHAR ime_composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    WCHAR ime_readingstring[16];
    int ime_cursor;

    SDL_nez_b32_t ime_candlist;
    WCHAR ime_candidates[MAX_CANDLIST][MAX_CANDLENGTH];
    DWORD ime_candcount;
    DWORD ime_candref;
    DWORD ime_candsel;
    UINT ime_candpgsize;
    int ime_candlistindexbase;
    SDL_nez_b32_t ime_candvertical;

    SDL_nez_b32_t ime_dirty;
    SDL_Rect ime_rect;
    SDL_Rect ime_candlistrect;
    int ime_winwidth;
    int ime_winheight;

    HKL ime_hkl;
    void* ime_himm32;
    UINT (WINAPI *GetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBuf, PINT pnErrorIndex, nez_b32_t *pfIsVertical, PUINT puMaxReadingLen);
    nez_b32_t (WINAPI *ShowReadingWindow)(HIMC himc, nez_b32_t bShow);
    LPINPUTCONTEXT2 (WINAPI *ImmLockIMC)(HIMC himc);
    nez_b32_t (WINAPI *ImmUnlockIMC)(HIMC himc);
    LPVOID (WINAPI *ImmLockIMCC)(HIMCC himcc);
    nez_b32_t (WINAPI *ImmUnlockIMCC)(HIMCC himcc);

    SDL_nez_b32_t ime_uiless;
    struct ITfThreadMgrEx *ime_threadmgrex;
    DWORD ime_uielemsinkcookie;
    DWORD ime_alpnsinkcookie;
    DWORD ime_openmodesinkcookie;
    DWORD ime_convmodesinkcookie;
    TSFSink *ime_uielemsink;
    TSFSink *ime_ippasink;
} SDL_VideoData;

extern SDL_nez_b32_t g_WindowsEnableMessageLoop;
extern SDL_nez_b32_t g_WindowFrameUsableWhileCursorHidden;

typedef struct IDirect3D9 IDirect3D9;
extern SDL_nez_b32_t D3D_LoadDLL( void **pD3DDLL, IDirect3D9 **pDirect3D9Interface );

#endif /* SDL_windowsvideo_h_ */

/* vi: set ts=4 sw=4 expandtab: */

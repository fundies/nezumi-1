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

#include <nezumi/window.h>
#include <nezumi/window/window.internal.h>

void       *g_nez_window_handle;
int         g_nez_window_width;
int         g_nez_window_height;
int         g_nez_window_x;
int         g_nez_window_y;
nez_b32_t   g_nez_window_visible;
nez_b32_t   g_nez_window_fullscreen;
nez_b32_t   g_nez_window_focus;

void *nez_window_get_handle(void)
{
    return g_nez_window_handle;
}

int nez_window_get_width(void)
{
    return g_nez_window_width;
}

int nez_window_get_height(void)
{
    return g_nez_window_height;
}

int nez_window_get_x(void)
{
    return g_nez_window_x;
}

int nez_window_get_y(void)
{
    return g_nez_window_y;
}

nez_b32_t nez_window_get_visible(void)
{
    return g_nez_window_visible;
}

nez_b32_t nez_window_get_fullscreen(void)
{
    return g_nez_window_fullscreen;
}

nez_b32_t nez_window_get_focus(void)
{
    return g_nez_window_focus;
}
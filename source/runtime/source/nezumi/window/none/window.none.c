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

nez_b32_t nez_window_init(const char *title, int width, int height)
{
    return NEZ_TRUE;
}

nez_b32_t nez_window_events(void)
{
    return NEZ_TRUE;
}

void nez_window_center(void)
{
}

void nez_window_set_title(const char *title)
{
}

void nez_window_set_size(int width, int height)
{
}

void nez_window_set_position(int x, int y)
{
}

void nez_window_set_visible(nez_b32_t visible)
{
}

void nez_window_set_fullscreen(nez_b32_t fullscreen)
{
}
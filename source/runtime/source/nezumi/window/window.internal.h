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

#ifndef NEZUMI_RUNTIME_WINDOW_INTERNAL_H
#define NEZUMI_RUNTIME_WINDOW_INTERNAL_H

#include <nezumi/types.h>

/** The handle of the window. */
extern void *g_nez_window_handle;

/** The width of the window. */
extern int g_nez_window_width;

/** The height of the window. */
extern int g_nez_window_height;

/** The X position of the window. */
extern int g_nez_window_x;

/** The Y position of the window. */
extern int g_nez_window_y;

/** Whether the window is visible. */
extern nez_b32_t g_nez_window_visible;

/** Whether the window is fullscreen. */
extern nez_b32_t g_nez_window_fullscreen;

/** Whether the window is focused. */
extern nez_b32_t g_nez_window_focus;

/**
 * Initializes the window module.
 * 
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 * 
 * @return True on success; false if an error occurred.
 */
extern nez_b32_t nez_window_init(const char *title, int width, int height);

/**
 * Handles incoming window events.
 * 
 * @return True if the window is still open; false otherwise.
 */
extern nez_b32_t nez_window_events(void);

#endif
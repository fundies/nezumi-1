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

#ifndef NEZUMI_RUNTIME_WINDOW_H
#define NEZUMI_RUNTIME_WINDOW_H

#include <nezumi/config.h>
#include <nezumi/types.h>

/**
 * Centers the window on the primary display.
 */
extern NEZUMI_API void nez_window_center(void);

/**
 * Sets the title of the window.
 * 
 * @param title The new title of the window.
 */
extern NEZUMI_API void nez_window_set_title(const char *title);

/**
 * Sets the size of the window.
 * 
 * @param width The new width of the window.
 * @param height The new height of the window.
 */
extern NEZUMI_API void nez_window_set_size(int width, int height);

/**
 * Sets the position of the window.
 * 
 * @param x The new X position of the window.
 * @param y The new Y position of the window.
 */
extern NEZUMI_API void nez_window_set_position(int x, int y);

/**
 * Sets whether the window is visible.
 * 
 * @param visible True if the window should be visible; false otherwise.
 */
extern NEZUMI_API void nez_window_set_visible(nez_b32_t visible);

/**
 * Sets whether the window is fullscreen.
 * 
 * @param fullscreen True if the window should be fullscreen; false otherwise.
 */
extern NEZUMI_API void nez_window_set_fullscreen(nez_b32_t fullscreen, nez_b32_t borderless);

/**
 * Gets the handle of the window.
 * 
 * @return The handle of the window.
 */
extern NEZUMI_API void *nez_window_get_handle(void);

/**
 * Gets the width of the window.
 * 
 * @return The width of the window.
 */
extern NEZUMI_API int nez_window_get_width(void);

/**
 * Gets the height of the window.
 * 
 * @return The height of the window.
 */
extern NEZUMI_API int nez_window_get_height(void);

/**
 * Gets the X position of the window.
 * 
 * @return The X position of the window.
 */
extern NEZUMI_API int nez_window_get_x(void);

/**
 * Gets the Y position of the window.
 * 
 * @return The Y position of the window.
 */
extern NEZUMI_API int nez_window_get_y(void);

/**
 * Gets whether the window is visible.
 * 
 * @return True if the window is visible; false otherwise.
 */
extern NEZUMI_API nez_b32_t nez_window_get_visible(void);

/**
 * Gets whether the window is fullscreen.
 * 
 * @return True if the window is fullscreen; false otherwise.
 */
extern NEZUMI_API nez_b32_t nez_window_get_fullscreen(void);

/**
 * Gets whether the window is focused.
 * 
 * @return True if the window is focused; false otherwise.
 */
extern NEZUMI_API nez_b32_t nez_window_get_focus(void);

#endif
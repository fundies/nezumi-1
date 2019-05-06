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
 * Defines the keys on the keyboard.
 */
enum
{
    /** Represents any defined key. */
    vk_any = -2,

    /** Represents an undefined key. */
    vk_none = -1,

    /** The number row 0 key. */
    vk_number_0,

    /** The number row 1 key. */
    vk_number_1,
        
    /** The number row 2 key. */
    vk_number_2,
        
    /** The number row 3 key. */
    vk_number_3,
        
    /** The number row 4 key. */
    vk_number_4,
        
    /** The number row 5 key. */
    vk_number_5,
        
    /** The number row 6 key. */
    vk_number_6,
        
    /** The number row 7 key. */
    vk_number_7,
        
    /** The number row 8 key. */
    vk_number_8,

    /** The number row 9 key. */
    vk_number_9,

    /** The keypad 0 key. */
    vk_keypad_0,

    /** The keypad 1 key. */
    vk_keypad_1,

    /** The keypad 2 key. */
    vk_keypad_2,

    /** The keypad 3 key. */
    vk_keypad_3,

    /** The keypad 4 key. */
    vk_keypad_4,

    /** The keypad 5 key. */
    vk_keypad_5,

    /** The keypad 6 key. */
    vk_keypad_6,

    /** The keypad 7 key. */
    vk_keypad_7,

    /** The keypad 8 key. */
    vk_keypad_8,

    /** The keypad 9 key. */
    vk_keypad_9,

    /** The keypad decimal key. */
    vk_keypad_decimal,

    /** The keypad divide key. */
    vk_keypad_divide,

    /** The keypad multiply key. */
    vk_keypad_multiply,

    /** The keypad subtract key. */
    vk_keypad_subtract,

    /** The keypad add key. */
    vk_keypad_add,

    /** The letter A key. */
    vk_a,

    /** The letter B key. */
    vk_b,

    /** The letter C key. */
    vk_c,

    /** The letter D key. */
    vk_d,
        
    /** The letter E key. */
    vk_e,
        
    /** The letter F key. */
    vk_f,
        
    /** The letter G key. */
    vk_g,
        
    /** The letter H key. */
    vk_h,
        
    /** The letter I key. */
    vk_i,
        
    /** The letter J key. */
    vk_j,
        
    /** The letter K key. */
    vk_k,
        
    /** The letter L key. */
    vk_l,
        
    /** The letter M key. */
    vk_m,
        
    /** The letter N key. */
    vk_n,
        
    /** The letter O key. */
    vk_o,
        
    /** The letter P key. */
    vk_p,
        
    /** The letter Q key. */
    vk_q,
        
    /** The letter R key. */
    vk_r,
        
    /** The letter S key. */
    vk_s,
        
    /** The letter T key. */
    vk_t,
        
    /** The letter U key. */
    vk_u,
        
    /** The letter V key. */
    vk_v,
        
    /** The letter W key. */
    vk_w,

    /** The letter X key. */
    vk_x,
        
    /** The letter Y key. */
    vk_y,
        
    /** The letter Z key. */
    vk_z,

    /** The left shift key. */
    vk_left_shift,

    /** The right shift key. */
    vk_right_shift,

    /** The left control key. */
    vk_left_control,

    /** The right control key. */
    vk_right_control,

    /** The left super key. */
    vk_left_super,

    /** The right super key. */
    vk_right_super,

    /** The spacebar key. */
    vk_space,

    /** The escape key. */
    vk_escape,

    /** The enter (or "return") key. */
    vk_enter,

    /** The tab key. */
    vk_tab,

    /** The backspace key. */
    vk_backspace,

    /** The insert key. */
    vk_insert,

    /** The delete key. */
    vk_delete,

    /** The home key. */
    vk_home,

    /** The end key. */
    vk_end,

    /** The left arrow key. */
    vk_left,

    /** The right arrow key. */
    vk_right,

    /** The down arrow key. */
    vk_down,

    /** The up arrow key. */
    vk_up,

    /** The page up key. */
    vk_page_up,

    /** The page down key. */
    vk_page_down,

    /** The pause key. */
    vk_pause,

    /** The print screen key. */
    vk_print_screen,

    /** The F1 function key. */
    vk_f1,

    /** The F2 function key. */
    vk_f2,

    /** The F3 function key. */
    vk_f3,

    /** The F4 function key. */
    vk_f4,

    /** The F5 function key. */
    vk_f5,

    /** The F6 function key. */
    vk_f6,

    /** The F7 function key. */
    vk_f7,

    /** The F8 function key. */
    vk_f8,

    /** The F9 function key. */
    vk_f9,

    /** The F10 function key. */
    vk_f10,

    /** The F11 function key. */
    vk_f11,

    /** The F12 function key. */
    vk_f12,

    /** The number of defined keys. */
    vk_last,
};

/**
 * Defines the buttons on the mouse.
 */
enum
{
    /** Represents any defined mouse button. */
    mb_any = -2,

    /** Represents an undefined mouse button. */
    mb_none = -1,

    /** The left mouse button. */
    mb_left,

    /** The right mouse button. */
    mb_right,

    /** The middle mouse button. */
    mb_middle,

    /** The first extra mouse button. */
    mb_ext_1,

    /** The second extra mouse button. */
    mb_ext_2,

    /** The number of defined mouse buttons. */
    mb_last,
};

/** The X position of the mouse relative to the game window. */
extern int g_nez_mouse_x;

/** The Y position of the mouse relative to the game window. */
extern int g_nez_mouse_y;

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
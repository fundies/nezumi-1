/**
 * Copyright (c) 2019 Greg Williamson
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

#include <nezumi/math.h>
#include <nezumi/window.h>
#include <nezumi/window/window.internal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

static SDL_Window *window = NULL;

/* The style of the window */
static Uint32 window_flags = SDL_WINDOW_RESIZABLE;

static inline int translate_key(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_0:              return vk_number_0;
        case SDLK_1:              return vk_number_1;
        case SDLK_2:              return vk_number_2;
        case SDLK_3:              return vk_number_3;
        case SDLK_4:              return vk_number_4;
        case SDLK_5:              return vk_number_5;
        case SDLK_6:              return vk_number_6;
        case SDLK_7:              return vk_number_7;
        case SDLK_8:              return vk_number_8;
        case SDLK_9:              return vk_number_9;
        case SDLK_KP_0:           return vk_keypad_0;
        case SDLK_KP_1:           return vk_keypad_1;
        case SDLK_KP_2:           return vk_keypad_2;
        case SDLK_KP_3:           return vk_keypad_3;
        case SDLK_KP_4:           return vk_keypad_4;
        case SDLK_KP_5:           return vk_keypad_5;
        case SDLK_KP_6:           return vk_keypad_6;
        case SDLK_KP_7:           return vk_keypad_7;
        case SDLK_KP_8:           return vk_keypad_8;
        case SDLK_KP_9:           return vk_keypad_9;
        case SDLK_KP_DECIMAL:     return vk_keypad_decimal;
        case SDLK_KP_DIVIDE:      return vk_keypad_divide;
        case SDLK_KP_MULTIPLY:    return vk_keypad_multiply;
        case SDLK_KP_MINUS:       return vk_keypad_subtract;
        case SDLK_KP_PLUS:        return vk_keypad_add;
        case SDLK_a:              return vk_a;
        case SDLK_b:              return vk_b;
        case SDLK_c:              return vk_c;
        case SDLK_d:              return vk_d;
        case SDLK_e:              return vk_e;
        case SDLK_f:              return vk_f;
        case SDLK_g:              return vk_g;
        case SDLK_h:              return vk_h;
        case SDLK_i:              return vk_i;
        case SDLK_j:              return vk_j;
        case SDLK_k:              return vk_k;
        case SDLK_l:              return vk_l;
        case SDLK_m:              return vk_m;
        case SDLK_n:              return vk_n;
        case SDLK_o:              return vk_o;
        case SDLK_p:              return vk_p;
        case SDLK_q:              return vk_q;
        case SDLK_r:              return vk_r;
        case SDLK_s:              return vk_s;
        case SDLK_t:              return vk_t;
        case SDLK_u:              return vk_u;
        case SDLK_v:              return vk_v;
        case SDLK_w:              return vk_w;
        case SDLK_x:              return vk_x;
        case SDLK_y:              return vk_y;
        case SDLK_z:              return vk_z;
        case SDLK_LSHIFT:         return vk_left_shift;
        case SDLK_RSHIFT:         return vk_right_shift;
        case SDLK_LCTRL:          return vk_left_control;
        case SDLK_RCTRL:          return vk_right_control;
        case SDLK_LGUI:           return vk_left_super;
        case SDLK_RGUI:           return vk_right_super;
        case SDLK_SPACE:          return vk_space;
        case SDLK_ESCAPE:         return vk_escape;
        case SDLK_RETURN:         return vk_enter;
        case SDLK_TAB:            return vk_tab;
        case SDLK_BACKSPACE:      return vk_backspace;
        case SDLK_INSERT:         return vk_insert;
        case SDLK_DELETE:         return vk_delete;
        case SDLK_HOME:           return vk_home;
        case SDLK_END:            return vk_end;
        case SDLK_LEFT:           return vk_left;
        case SDLK_RIGHT:          return vk_right;
        case SDLK_DOWN:           return vk_down;
        case SDLK_UP:             return vk_up;
        case SDLK_PAGEUP:         return vk_page_up;
        case SDLK_PAGEDOWN:       return vk_page_down;
        case SDLK_PAUSE:          return vk_pause;
        case SDLK_PRINTSCREEN:    return vk_print_screen;
        case SDLK_F1:             return vk_f1;
        case SDLK_F2:             return vk_f2;
        case SDLK_F3:             return vk_f3;
        case SDLK_F4:             return vk_f4;
        case SDLK_F5:             return vk_f5;
        case SDLK_F6:             return vk_f6;
        case SDLK_F7:             return vk_f7;
        case SDLK_F8:             return vk_f8;
        case SDLK_F9:             return vk_f9;
        case SDLK_F10:            return vk_f10;
        case SDLK_F11:            return vk_f11;
        case SDLK_F12:            return vk_f12;
        case SDLK_F13:
        case SDLK_F14:
        case SDLK_F15:
        case SDLK_F16:
        case SDLK_F17:
        case SDLK_F18:
        case SDLK_F19:
        case SDLK_F20:
        case SDLK_F21:
        case SDLK_F22:
        case SDLK_F23:
        case SDLK_F24:
        case SDLK_AC_BACK:
        case SDLK_AC_BOOKMARKS:
        case SDLK_AC_FORWARD:
        case SDLK_AC_HOME:
        case SDLK_AC_REFRESH:
        case SDLK_AC_SEARCH:
        case SDLK_AC_STOP:
        case SDLK_AGAIN:
        case SDLK_ALTERASE:
        case SDLK_QUOTE:
        case SDLK_APPLICATION:
        case SDLK_AUDIOMUTE:
        case SDLK_AUDIONEXT:
        case SDLK_AUDIOPREV:
        case SDLK_AUDIOPLAY:
        case SDLK_AUDIOSTOP:
        case SDLK_BACKSLASH:
        case SDLK_BRIGHTNESSDOWN:
        case SDLK_BRIGHTNESSUP:
        case SDLK_CALCULATOR:
        case SDLK_CAPSLOCK:
        case SDLK_CLEAR:
        case SDLK_CLEARAGAIN:
        case SDLK_COMMA:
        case SDLK_COMPUTER:
        case SDLK_COPY:
        case SDLK_CRSEL:
        case SDLK_CURRENCYSUBUNIT:
        case SDLK_CURRENCYUNIT:
        case SDLK_CUT:
        case SDLK_DECIMALSEPARATOR:
        case SDLK_DISPLAYSWITCH:
        case SDLK_EJECT:
        case SDLK_EQUALS:
        case SDLK_EXECUTE:
        case SDLK_EXSEL:
        case SDLK_FIND:
        case SDLK_BACKQUOTE:
        case SDLK_HELP:
        case SDLK_KBDILLUMDOWN:
        case SDLK_KBDILLUMTOGGLE:
        case SDLK_KBDILLUMUP:
        case SDLK_KP_00:
        case SDLK_KP_000:
        case SDLK_KP_A:
        case SDLK_KP_B:
        case SDLK_KP_C:
        case SDLK_KP_D:
        case SDLK_KP_E:
        case SDLK_KP_F:
        case SDLK_KP_AMPERSAND:
        case SDLK_KP_AT:
        case SDLK_KP_BACKSPACE:
        case SDLK_KP_BINARY:
        case SDLK_KP_CLEAR:
        case SDLK_KP_CLEARENTRY:
        case SDLK_KP_COLON:
        case SDLK_KP_COMMA:
        case SDLK_KP_DBLAMPERSAND:
        case SDLK_KP_DBLVERTICALBAR:
        case SDLK_KP_EQUALS:
        case SDLK_KP_EQUALSAS400:
        case SDLK_KP_EXCLAM:
        case SDLK_KP_GREATER:
        case SDLK_KP_HASH:
        case SDLK_KP_HEXADECIMAL:
        case SDLK_KP_LEFTBRACE:
        case SDLK_KP_LEFTPAREN:
        case SDLK_KP_MEMADD:
        case SDLK_KP_MEMCLEAR:
        case SDLK_KP_MEMDIVIDE:
        case SDLK_KP_MEMMULTIPLY:
        case SDLK_KP_MEMRECALL:
        case SDLK_KP_MEMSTORE:
        case SDLK_KP_MEMSUBTRACT:
        case SDLK_KP_PERCENT:
        case SDLK_KP_PERIOD:
        case SDLK_KP_PLUSMINUS:
        case SDLK_KP_POWER:
        case SDLK_KP_RIGHTBRACE:
        case SDLK_KP_RIGHTPAREN:
        case SDLK_KP_SPACE:
        case SDLK_KP_TAB:
        case SDLK_KP_VERTICALBAR:
        case SDLK_KP_XOR:
        case SDLK_LALT:
        case SDLK_LEFTBRACKET:
        case SDLK_MAIL:
        case SDLK_MEDIASELECT:
        case SDLK_MENU:
        case SDLK_MODE:
        case SDLK_MUTE:
        case SDLK_NUMLOCKCLEAR:
        case SDLK_OPER:
        case SDLK_OUT:
        case SDLK_PASTE:
        case SDLK_PERIOD:
        case SDLK_POWER:
        case SDLK_PRIOR:
        case SDLK_RALT:
        case SDLK_RETURN2:
        case SDLK_RIGHTBRACKET:
        case SDLK_SCROLLLOCK:
        case SDLK_SELECT:
        case SDLK_SEMICOLON:
        case SDLK_SEPARATOR:
        case SDLK_SLASH:
        case SDLK_SLEEP:
        case SDLK_STOP:
        case SDLK_SYSREQ:
        case SDLK_THOUSANDSSEPARATOR:
        case SDLK_UNDO:
        case SDLK_VOLUMEDOWN:
        case SDLK_VOLUMEUP:
        case SDLK_WWW:
        case SDLK_AMPERSAND:
        case SDLK_ASTERISK:
        case SDLK_AT:
        case SDLK_CARET:
        case SDLK_COLON:
        case SDLK_DOLLAR:
        case SDLK_EXCLAIM:
        case SDLK_GREATER:
        case SDLK_HASH:
        case SDLK_LEFTPAREN:
        case SDLK_LESS:
        case SDLK_PERCENT:
        case SDLK_PLUS:
        case SDLK_QUESTION:
        case SDLK_QUOTEDBL:
        case SDLK_RIGHTPAREN:
        case SDLK_UNDERSCORE:
        case SDLK_UNKNOWN:
        default:                  return vk_none;
    }
}

static inline int translate_mouse_button(unsigned int button)
{
    switch (button) 
    {
        case SDL_BUTTON_LEFT:     return mb_left;
        case SDL_BUTTON_MIDDLE:   return mb_middle;
        case SDL_BUTTON_RIGHT:    return mb_right;
        case SDL_BUTTON_X1:       return mb_ext_1;
        case SDL_BUTTON_X2:       return mb_ext_2;
        default:                  return mb_none;
    }
}

static nez_b32_t window_event(SDL_Event *event)
{
    switch (event->window.event)
    {
        case SDL_WINDOWEVENT_RESIZED:
        {
            g_nez_window_width = event->window.data1;
            g_nez_window_height = event->window.data2;

            break;
        }

        case SDL_WINDOWEVENT_MOVED:
        {
            g_nez_window_x = event->window.data1;
            g_nez_window_y = event->window.data2;

            break;
        }

        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
            g_nez_window_focus = NEZ_TRUE;

            break;
        }

        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
            g_nez_window_focus = NEZ_FALSE;

            break;
        }

        case SDL_WINDOWEVENT_SHOWN:           break;
        case SDL_WINDOWEVENT_HIDDEN:          break;
        case SDL_WINDOWEVENT_EXPOSED:         break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:    break;
        case SDL_WINDOWEVENT_MINIMIZED:       break;
        case SDL_WINDOWEVENT_MAXIMIZED:       break;
        case SDL_WINDOWEVENT_RESTORED:        break;
        case SDL_WINDOWEVENT_ENTER:           break;
        case SDL_WINDOWEVENT_LEAVE:           break;
        case SDL_WINDOWEVENT_CLOSE:           break;
        case SDL_WINDOWEVENT_TAKE_FOCUS:      break;
        case SDL_WINDOWEVENT_HIT_TEST:        break;
        default:                              break;
    }

    return NEZ_TRUE;
}

nez_b32_t nez_window_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT:
        {
            window_event(&event);
            break;
        }

        case SDL_QUIT:    return 0;

        case SDL_KEYDOWN:
        {
            int key = translate_key(event.key.keysym.sym);

            /* Set Key State */
            if (key != vk_none)
                g_nez_keyboard_current[key] = NEZ_TRUE;

            /* Set Any State */
            g_nez_keyboard_any_down = NEZ_TRUE;
            g_nez_keyboard_any_pressed = NEZ_TRUE;

            break;
        }

        case SDL_KEYUP:
        {
            int key = translate_key(event.key.keysym.sym);

            /* Reset Key State */
            if (key != vk_none)
              g_nez_keyboard_current[key] = NEZ_FALSE;

            /* Reset Any State */
            g_nez_keyboard_any_down = NEZ_TRUE;
            g_nez_keyboard_any_released = NEZ_TRUE;

            break;
        }

        case SDL_MOUSEMOTION:
        {
            /* Sometimes these positions lie slightly outside of the client
             * area of the window, so we should manually clamp them ourselves. */
            g_nez_mouse_x = nez_clamp(event.motion.x, 0, g_nez_window_width);
            g_nez_mouse_y = nez_clamp(event.motion.y, 0, g_nez_window_height);

            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            int btn = translate_mouse_button(event.button.button);

            /* Set State */
            g_nez_mouse_current[btn] = NEZ_TRUE;
            g_nez_mouse_any_down = NEZ_TRUE;
            g_nez_mouse_any_pressed = NEZ_TRUE;

            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            int btn = translate_mouse_button(event.button.button);

            /* Reset State */
            g_nez_mouse_current[btn] = NEZ_FALSE;
            g_nez_mouse_any_released = NEZ_TRUE;

            break;
        }

        case SDL_MOUSEWHEEL:                  break;
        case SDL_TEXTEDITING:                 break;
        case SDL_TEXTINPUT:                   break;
        case SDL_JOYAXISMOTION:               break;
        case SDL_JOYBALLMOTION:               break;
        case SDL_JOYHATMOTION:                break;
        case SDL_JOYBUTTONDOWN:               break;
        case SDL_JOYBUTTONUP:                 break;
        case SDL_JOYDEVICEADDED:              break;
        case SDL_JOYDEVICEREMOVED:            break;
        case SDL_CONTROLLERAXISMOTION:        break;
        case SDL_CONTROLLERBUTTONDOWN:        break;
        case SDL_CONTROLLERBUTTONUP:          break;
        case SDL_CONTROLLERDEVICEADDED:       break;
        case SDL_CONTROLLERDEVICEREMOVED:     break;
        case SDL_CONTROLLERDEVICEREMAPPED:    break;
        case SDL_AUDIODEVICEADDED:            break;
        case SDL_AUDIODEVICEREMOVED:          break;
        case SDL_FINGERMOTION:                break;
        case SDL_FINGERDOWN:                  break;
        case SDL_FINGERUP:                    break;
        case SDL_MULTIGESTURE:                break;
        case SDL_DOLLARGESTURE:               break;
        case SDL_DOLLARRECORD:                break;
        case SDL_DROPFILE:                    break;
        case SDL_DROPTEXT:                    break;
        case SDL_DROPBEGIN:                   break;
        case SDL_DROPCOMPLETE:                break;
        default:                              break;
        }
    }

    return NEZ_TRUE;
}

nez_b32_t nez_window_init(const char *title, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    if (window == NULL) 
        return NEZ_FALSE; 
    
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    g_nez_window_handle = (void*)wmInfo.info.win.window;
    
    return NEZ_TRUE;
}

void nez_window_set_title(const char *title)
{
    SDL_SetWindowTitle(window, title);
}

void nez_window_center(void)
{
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void nez_window_set_size(int width, int height)
{
    SDL_SetWindowSize(window, width, height);
}

void nez_window_set_position(int x, int y)
{
    SDL_SetWindowPosition(window, x, y);
}

void nez_window_set_visible(nez_b32_t visible)
{
    (visible) ? SDL_ShowWindow(window) : SDL_HideWindow(window);
}

void nez_window_set_fullscreen(nez_b32_t fullscreen, nez_b32_t borderless)
{
    int ret;

    if (fullscreen) 
    {
        if (borderless)
            ret = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        else
            ret = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    else ret = SDL_SetWindowFullscreen(window, 0);

    if (ret != 0); /* print error */
}
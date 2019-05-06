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

#include <nezumi/window.h>
#include <nezumi/window/window.internal.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

static SDL_Window* window = NULL;

// The style of the window.
static Uint32 window_flags = SDL_WINDOW_RESIZABLE;

static inline int translate_key(SDL_Keycode key)
{
    switch (key)
    {
        /*case SDLK_LEFT:            return vk_left;
        case SDLK_RIGHT:           return vk_right;
        case SDLK_UP:              return vk_up;
        case SDLK_DOWN:            return vk_down;
        case SDLK_TAB:             return vk_tab;
        case SDLK_RETURN:          return vk_enter;
        case SDLK_SPACE:           return vk_space;
        case SDLK_LSHIFT:          return vk_shift;
        case SDLK_LCTRL:           return vk_control;
        case SDLK_LALT:            return vk_alt;
        case SDLK_RSHIFT:          return vk_shift;
        case SDLK_RCTRL:           return vk_ctrl;
        case SDLK_RALT:            return vk_alt;
        case SDLK_0:               return vk_numpad0;
        case SDLK_1:               return vk_numpad1;
        case SDLK_2:               return vk_numpad2;
        case SDLK_3:               return vk_numpad3;
        case SDLK_4:               return vk_numpad4;
        case SDLK_5:               return vk_numpad5;
        case SDLK_6:               return vk_numpad6;
        case SDLK_7:               return vk_numpad7;
        case SDLK_8:               return vk_numpad8;
        case SDLK_9:               return vk_numpad9;
        case SDLK_KP_MULTIPLY:     return vk_multiply;
        case SDLK_KP_PLUS:         return vk_plus;
        case SDLK_KP_MINUS:        return vk_minus;
        case SDLK_KP_DECIMAL:      return vk_decimal;
        case SDLK_KP_DIVIDE:       return vk_divide;
        case SDLK_F1:              return vk_f1;
        case SDLK_F2:              return vk_f2;
        case SDLK_F3:              return vk_f3;
        case SDLK_F4:              return vk_f4;
        case SDLK_F5:              return vk_f5;
        case SDLK_F6:              return vk_f6;
        case SDLK_F7:              return vk_f7;
        case SDLK_F8:              return vk_f8;
        case SDLK_F9:              return vk_f9;
        case SDLK_F10:             return vk_f10;
        case SDLK_F11:             return vk_f11;
        case SDLK_F12:             return vk_f12;
        case SDLK_BACKSPACE:       return vk_backspace;
        case SDLK_ESCAPE:          return vk_escape;
        case SDLK_PAGEUP:          return vk_pageup;
        case SDLK_PAGEDOWN:        return vk_pagedown;
        case SDLK_END:             return vk_end;
        case SDLK_HOME:            return vk_home;
        case SDLK_INSERT:          return vk_insert;
        case SDLK_DELETE:          return vk_delete;
        case SDLK_PRINTSCREEN:     return vk_printscreen;
        case SDLK_CAPSLOCK:        return vk_caps;
        case SDLK_SCROLLLOCK:      return vk_scroll;
        case SDLK_PAUSE:           return vk_pause;
        case SDLK_LGUI:            return vk_lsuper;
        case SDLK_RGUI:            return vk_rsuper;*/
    default:                   return -1;
    }
}

static inline int translate_mouse_button(unsigned int button)
{
    switch (button) {
        /*case SDL_BUTTON_LEFT:     return mb_left;
        case SDL_BUTTON_MIDDLE:   return mb_middle;
        case SDL_BUTTON_RIGHT:    return mb_right;
        case SDL_BUTTON_X1:       return mb_x1;
        case SDL_BUTTON_X2:       return mb_x2;*/
    default:                  return -1;
    }
}

static nez_b32_t window_event(SDL_Event* event)
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

            // Set Key State
            //if (key != vk_none)
                //g_nez_keyboard_current[key] = true;

            // Set Any State
            //g_nez_keyboard_any_down = true;
            //g_nez_keyboard_any_pressed = true;

            break;
        }

        case SDL_KEYUP:
        {
            int key = translate_key(event.key.keysym.sym);

            // Reset Key State
            //if (key != vk_none)
              //g_nez_keyboard_current[key] = false;

            // Reset Any State
            //g_nez_keyboard_any_down = false;
            //g_nez_keyboard_any_released = true;

            break;
        }

        case SDL_MOUSEMOTION:
        {
            // Sometimes these positions lie slightly outside of the client
            // area of the window, so we should manually clamp them ourselves.
            //g_mouse_x = clamp(event.x, 0, g_window_width);
            //g_mouse_y = clamp(event.y, 0, g_window_height);

            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            int btn = translate_mouse_button(event.button.button);

            // Set State
            //g_nez_mouse_current[btn] = true;
            //g_nez_mouse_any_down = true;
            //g_nez_mouse_any_pressed = true;

            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            int btn = translate_mouse_button(event.button.button);

            // Reset State
            //g_nez_mouse_current[btn] = false;
            //g_nez_mouse_any_released = true;

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

nez_b32_t nez_window_init(const char* title, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    if (window == NULL) return NEZ_FALSE; 
    
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    g_nez_window_handle = (void*)wmInfo.info.win.window;
    
    return NEZ_TRUE;
}

void nez_window_set_title(const char* title)
{
    SDL_SetWindowTitle(window, title);
}

void nez_window_center()
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

    if (fullscreen) {
        if (borderless)
            ret = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        else
            ret = SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    else ret = SDL_SetWindowFullscreen(window, 0);

    if (ret != 0); // print error
}
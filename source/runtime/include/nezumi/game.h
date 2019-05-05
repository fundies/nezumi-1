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

#ifndef NEZUMI_RUNTIME_GAME_H
#define NEZUMI_RUNTIME_GAME_H

#include <nezumi/config.h>

struct nez_game_config
{
    /** The title of the window. */
    const char *window_title;

    /** The width of the window. */
    int window_width;

    /** The height of the window. */
    int window_height;

    /** The function to call when the game is started. */
    void (*callback_init)(void);

    /** The function to call when the game is exited. */
    void (*callback_exit)(void);

    /** The function to call when the game is updated. */
    void (*callback_step)(void);

    /** The function to call when the game is rendered. */
    void (*callback_draw)(void);
};

/**
 * Initializes the game and begins running the main loop.
 * 
 * @param argc The command-line argument count.
 * @param argv The command-line argument array.
 * @param config A pointer to the structure providing the initial configuration
 *               of the game.
 * 
 * @return The exit code for the application.
 */
extern NEZUMI_API int nez_game_run(int argc, char **argv,
                                    const struct nez_game_config *config);

/**
 * Requests the game to exit on the next frame.
 */
extern NEZUMI_API void nez_game_end(void);

#endif
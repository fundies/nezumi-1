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

#include <stdlib.h>

#include <nezumi/game.h>
#include <nezumi/window.h>
#include <nezumi/types.h>

#include <nezumi/window/window.internal.h>

/* Whether the game has been flagged to exit. */
static nez_b32_t exiting;

/* Whether the game has been painted at least once. */
static nez_b32_t painted;

int nez_game_main(int argc, char **argv,
                  const struct temp_callbacks *callbacks)
{
    /* Initialize Window */
    if (!nez_window_init("Nezumi Game", 1280, 720))
        return EXIT_FAILURE;

    /* Initialize Game */
    callbacks->init();

    /* Game Loop */
    while (!exiting)
    {
        /* Window Events */
        if (!nez_window_events())
            break;

        /* Update Game */
        callbacks->step();

        /* Render Game */
        callbacks->draw();

        /* Frame Painted */
        if (!painted)
        {
            painted = NEZ_TRUE;

            /* Show the window only after the first frame has been fully
             * rendered so the user doesn't see an unpainted window while
             * the game starts up. */
            nez_window_set_visible(NEZ_TRUE);
        }
    }

    /* Shutdown Game */
    callbacks->exit();

    /* Success */
    return EXIT_SUCCESS;
}

void nez_game_exit(void)
{
    exiting = NEZ_TRUE;
}
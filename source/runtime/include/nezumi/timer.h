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

#ifndef NEZUMI_RUNTIME_TIMER_H
#define NEZUMI_RUNTIME_TIMER_H

#include <nezumi/config.h>

/**
 * Gets the current value of the system timer.
 * 
 * This function gets the total elapsed time since the start of the game
 * (measured in seconds) as determined by the system's high-resolution timer.
 * 
 * @return The current value of the system timer.
 */
extern NEZUMI_API double nez_timer_get();

#endif
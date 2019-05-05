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

#include <nezumi/timer.h>
#include <nezumi/timer/timer.internal.h>

#include <windows.h>

static double frequency;
static double offset;

nez_b32_t nez_timer_init(void)
{
    LARGE_INTEGER result;

    /* Get Frequency */
    if (!QueryPerformanceFrequency(&result))
        return NEZ_FALSE;

    frequency = (double)result.QuadPart;

    /* Get Offset */
    if (!QueryPerformanceCounter(&result))
        return NEZ_FALSE;

    offset = (double)result.QuadPart;

    /* Success */
    return NEZ_TRUE;
}

double nez_timer_get(void)
{
    LARGE_INTEGER current;

    /* Get Current Time */
    QueryPerformanceCounter(&current);

    /* Calculate Timer Value */
    return ((double)current.QuadPart - offset) / frequency;
}
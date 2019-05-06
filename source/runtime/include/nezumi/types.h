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

#ifndef NEZUMI_RUNTIME_TYPES_H
#define NEZUMI_RUNTIME_TYPES_H

/* Define Integer Types */
#if defined(_MSC_VER)
    /* MSVC */
    typedef signed __int8       nez_s8_t;
    typedef signed __int16      nez_s16_t;
    typedef signed __int32      nez_s32_t;
    typedef signed __int64      nez_s64_t;

    typedef unsigned __int8     nez_u8_t;
    typedef unsigned __int16    nez_u16_t;
    typedef unsigned __int32    nez_u32_t;
    typedef unsigned __int64    nez_u64_t;
#else
    /* Other Compiler */
    typedef signed char         nez_s8_t;
    typedef signed short        nez_s16_t;
    typedef signed int          nez_s32_t;
    typedef signed long long    nez_s64_t;

    typedef unsigned char       nez_u8_t;
    typedef unsigned short      nez_u16_t;
    typedef unsigned int        nez_u32_t;
    typedef unsigned long long  nez_u64_t;
#endif

/* Define nez_b32_tean Types */
typedef nez_s8_t    nez_b8_t;
typedef nez_s32_t   nez_b32_t;

/* Define nez_b32_tean Constants */
#define NEZ_TRUE    1
#define NEZ_FALSE   0

#endif
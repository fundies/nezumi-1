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

#ifndef NEZUMI_RUNTIME_CONFIG_H
#define NEZUMI_RUNTIME_CONFIG_H

/* Define Import/Export Macros */
#if defined(NEZUMI_STATIC)
    /* Static Library */
    #define NEZUMI_API
#else
    /* Shared Library */
    #if defined(_MSC_VER)
        /* MSVC */
        #if defined(MSVC_BUILD_DLL)
            #define NEZUMI_API __declspec(dllexport)
        #else
            #define NEZUMI_API __declspec(dllimport)
        #endif
    #elif defined(__GNUC__)
        /* GCC */
        #if __GNUC__ >= 4
            #define NEZUMI_API __attribute__ ((visibility ("default")))
        #else
            #define NEZUMI_API
        #endif
    #elif defined(__clang__)
        /* Clang */
        #define NEZUMI_API __attribute__ ((visibility ("default")))
    #else
        /* Other Compiler */
        #define NEZUMI_API
    #endif
#endif

/* Define Inline Macros */
#if defined(_MSC_VER)
    /* MSVC */
    #define NEZUMI_INLINE __forceinline
#elif defined(__GNUC__)
    /* GCC */
    #define NEZUMI_INLINE __attribute__ ((always_inline))
#else
    /* Unknown Compiler */
    #if __STDC_VERSION__ >= 199901L || defined(__cplusplus)
        /* C99 / C++ */
        #define NEZUMI_INLINE inline
    #else
        /* C89 */
        #define NEZUMI_INLINE
    #endif
#endif

#endif
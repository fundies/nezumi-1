INCLUDE (ExternalProject)

# Vendor Includes
INCLUDE_DIRECTORIES ("${CMAKE_BINARY_DIR}/vendor/include")

# Set Runtime Options
SET (RUNTIME_STATIC ON CACHE BOOL "Whether to build the runtime as a static or shared library.")
SET (RUNTIME_PARANOID ON CACHE BOOL "Enables speed-sapping runtime error checks and assertions. Despite its name, you should probably ship the game with these enabled.")

# Get Runtime Sources
SET (
    SOURCE_RUNTIME

    "source/nezumi/game.c"

    "source/nezumi/window/window.internal.c"
)

# Define Empty Modules
NEZUMI_MODULE_ENTRY (RUNTIME_MODULE_WINDOW "None" SOURCES "source/nezumi/window/none/window.none.c")
NEZUMI_MODULE_ENTRY (RUNTIME_MODULE_TIMER "None" SOURCES "source/nezumi/timer/none/timer.none.c")

# Define Platform Modules
IF (NEZUMI_PLATFORM_WINDOWS)
    # Windows
    NEZUMI_MODULE_DEFAULT (RUNTIME_MODULE_WINDOW "Win32")
    NEZUMI_MODULE_DEFAULT (RUNTIME_MODULE_TIMER "Win32")

    # Windows - Window
    NEZUMI_MODULE_ENTRY (RUNTIME_MODULE_WINDOW "Win32" SOURCES "source/nezumi/window/win32/window.win32.c")

    # SDL2 - Window
    NEZUMI_MODULE_ENTRY (RUNTIME_MODULE_WINDOW "SDL2" SOURCES "source/nezumi/window/sdl2/window.sdl2.c" LIBRARIES "SDL2main;SDL2-static;imm32;version;winmm" EXTERNAL "SDL2" PROVIDES "SDL2main;SDL2-static")

    # Windows - Timer
    NEZUMI_MODULE_ENTRY (RUNTIME_MODULE_TIMER "Win32" SOURCES "source/nezumi/timer/win32/timer.win32.c")
ELSE ()
    # Other Platform
    MESSAGE (WARNING "This platform has no supported runtime modules!")
ENDIF ()

# Define Module Options
NEZUMI_MODULE_OPTION (RUNTIME_MODULE_WINDOW "The backend to use for the runtime's window module.")
NEZUMI_MODULE_OPTION (RUNTIME_MODULE_TIMER "The backend to use for the runtime's timer module.")

# Gather Sources
SET (
    SOURCE_RUNTIME

    ${SOURCE_RUNTIME}
    ${SOURCE_RUNTIME_MODULE_WINDOW}
    ${SOURCE_RUNTIME_MODULE_TIMER}
)

# Add Target
IF (RUNTIME_STATIC)
    # Add Static Library
    ADD_LIBRARY(nezumi-runtime STATIC ${SOURCE_RUNTIME})

    # Add Static Definition
    TARGET_COMPILE_DEFINITIONS (nezumi-runtime PUBLIC "NEZUMI_STATIC")
ELSE ()
    # Add Shared Library
    ADD_LIBRARY(nezumi-runtime SHARED ${SOURCE_RUNTIME})

    # MSVC needs to know when we're building the actual library so we can
    # properly mark symbols to be exported to the DLL. On other compilers,
    # we just use the same attributes for importing/exporting.
    IF (NEZUMI_COMPILER_MSVC)
        TARGET_COMPILE_DEFINITIONS (nezumi-runtime PRIVATE "MSVC_BUILD_DLL")
    ENDIF ()
ENDIF ()

# Add Target Directories
TARGET_INCLUDE_DIRECTORIES (nezumi-runtime PUBLIC "source" "include")

# Add Target Definitions
IF (RUNTIME_PARANOID)
    TARGET_COMPILE_DEFINITIONS (nezumi-runtime PUBLIC "NEZUMI_PARANOID")
ENDIF ()

# Add Target Modules
NEZUMI_MODULE_TARGET (RUNTIME_MODULE_WINDOW nezumi-runtime)
NEZUMI_MODULE_TARGET (RUNTIME_MODULE_TIMER nezumi-runtime)
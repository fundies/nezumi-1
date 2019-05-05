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
NEZUMI_MODULE_ENTRY (RUNTIME_WINDOW_MODULE "None" SOURCES "source/nezumi/window/none/window.none.c")

# Define Platform Modules
IF (NEZUMI_PLATFORM_WINDOWS)
    # Windows
    NEZUMI_MODULE_DEFAULT (RUNTIME_WINDOW_MODULE "Win32")

    # Windows - Window
    NEZUMI_MODULE_ENTRY (RUNTIME_WINDOW_MODULE "Win32" SOURCES "source/nezumi/window/win32/window.win32.c")
ELSE ()
    # Other Platform
    MESSAGE (WARNING "This platform has no supported runtime modules!")
ENDIF ()

# Define Module Options
NEZUMI_MODULE_OPTION (RUNTIME_WINDOW_MODULE "The backend to use for the runtime's window module.")

# Gather Sources
SET (
    SOURCE_RUNTIME

    ${SOURCE_RUNTIME}
    ${SOURCE_RUNTIME_WINDOW_MODULE}
)

MESSAGE (WARNING ${SOURCE_RUNTIME_WINDOW_MODULE})

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
NEZUMI_MODULE_TARGET (SOURCE_RUNTIME_WINDOW nezumi-runtime)
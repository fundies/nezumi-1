# Defines the default value of the specified module.
MACRO (NEZUMI_MODULE_DEFAULT MODULE DEFAULT)
    SET ("${MODULE}_DEFAULT" ${DEFAULT})
ENDMACRO ()

# Defines an entry for the specified module.
MACRO (NEZUMI_MODULE_ENTRY MODULE ENTRY)
    # Parse and store the argument values.
    CMAKE_PARSE_ARGUMENTS ("ARGS" "" "" "SOURCES;LIBRARIES;EXTERNAL;PROVIDES" ${ARGN})

    SET ("${MODULE}_${ENTRY}_SOURCES" ${ARGS_SOURCES})
    SET ("${MODULE}_${ENTRY}_LIBRARIES" ${ARGS_LIBRARIES})
    SET ("${MODULE}_${ENTRY}_EXTERNAL" ${ARGS_EXTERNAL})
    SET ("${MODULE}_${ENTRY}_PROVIDES" ${ARGS_PROVIDES})

    # Add the entry to the module's entry list.
    LIST (APPEND "${MODULE}_ENTRIES" ${ENTRY})
ENDMACRO ()

# Defines a cache option for the specified module.
MACRO (NEZUMI_MODULE_OPTION MODULE DOCSTRING)
    # Set the cache option to the module's default value.
    SET (${MODULE} "${${MODULE}_DEFAULT}" CACHE STRING ${DOCSTRING})
    
    # Set the STRINGS property to the module's entry list.
    SET_PROPERTY (CACHE ${MODULE} PROPERTY STRINGS "${${MODULE}_ENTRIES}")

    # Output the sources for the selected entry.
    SET ("SOURCE_${MODULE}" "${${MODULE}_${${MODULE}}_SOURCES}")
ENDMACRO ()

# Links a module's dependencies to the specified target.
MACRO (NEZUMI_MODULE_TARGET MODULE TARGET)
    # Add External Projects
    IF (NOT "${${MODULE}_${${MODULE}}_EXTERNAL}" STREQUAL "")
        FOREACH (external_project "${${MODULE}_${${MODULE}}_EXTERNAL}")
            NEZUMI_EXTERNAL_PROJECT (${external_project} ${TARGET} "${${MODULE}_${${MODULE}}_PROVIDES}")
        ENDFOREACH ()
    ENDIF ()

    TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "${${MODULE}_${${MODULE}}_LIBRARIES}")
ENDMACRO ()

# Adds an external project dependency to the specified target.
MACRO (NEZUMI_EXTERNAL_PROJECT PROJECT TARGET PROVIDES)
    
    set(PRODUCTS)

    IF (MSVC)
      IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET(LIB_SUFFIX "d.lib")
      ELSE()
        SET(LIB_SUFFIX ".lib")
      ENDIF()
    ENDIF (MSVC)
    
    IF (NOT "${PROVIDES}" STREQUAL "")
        FOREACH (lib ${PROVIDES})
            ADD_LIBRARY ("${lib}" UNKNOWN IMPORTED)
            SET_TARGET_PROPERTIES ("${lib}" PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/vendor/lib/${lib}${LIB_SUFFIX}")
            LIST (APPEND PRODUCTS "${CMAKE_BINARY_DIR}/vendor/lib/${lib}${LIB_SUFFIX}")
        ENDFOREACH ()
    ENDIF ()

    ExternalProject_Add (
        ${PROJECT}
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor/"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/${PROJECT}/"
        BUILD_BYPRODUCTS ${PRODUCTS}
    )

    ADD_DEPENDENCIES (${TARGET} ${PROJECT})

ENDMACRO ()
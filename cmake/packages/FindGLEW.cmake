include(FindPackageHandleStandardArgs)

if (WIN32)

    find_path(GLEW_INCLUDE_DIR
        NAMES
            GL/glew.h
        HINTS
            "${GLEW_LOCATION}/include"
            "$ENV{GLEW_LOCATION}/include"
        PATHS
            "$ENV{PROGRAMFILES}/GLEW/include"
            "${PROJECT_SOURCE_DIR}/extern/glew/include"
        DOC "The directory where GL/glew.h resides" )

    if ("${CMAKE_GENERATOR}" MATCHES "[Ww]in64")
        set(ARCH x64)
    else()
        set(ARCH Win32)
    endif()

    find_library(GLEW_LIBRARY
        NAMES
            glew GLEW glew32s glew32
        HINTS
            "${GLEW_LOCATION}/lib"
            "$ENV{GLEW_LOCATION}/lib"
        PATHS
            "$ENV{PROGRAMFILES}/GLEW/lib"
            "${PROJECT_SOURCE_DIR}/extern/glew/bin"
            "${PROJECT_SOURCE_DIR}/extern/glew/lib"
        PATH_SUFFIXES
            Release/${ARCH}
        DOC "The GLEW library")
endif ()

if (${CMAKE_HOST_UNIX})
    find_path( GLEW_INCLUDE_DIR
        NAMES
            GL/glew.h
        HINTS
            "${GLEW_LOCATION}/include"
            "$ENV{GLEW_LOCATION}/include"
        PATHS
            /usr/include
            /usr/local/include
            /sw/include
            /opt/local/include
            NO_DEFAULT_PATH
            DOC "The directory where GL/glew.h resides"
    )
    find_library( GLEW_LIBRARY
        NAMES
            GLEW glew
        HINTS
            "${GLEW_LOCATION}/lib"
            "$ENV{GLEW_LOCATION}/lib"
        PATHS
            /usr/lib64
            /usr/lib
            /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}
            /usr/local/lib64
            /usr/local/lib
            /sw/lib
            /opt/local/lib
            NO_DEFAULT_PATH
            DOC "The GLEW library")
endif ()

if (GLEW_INCLUDE_DIR AND EXISTS "${GLEW_INCLUDE_DIR}/GL/glew.h")

   file(STRINGS "${GLEW_INCLUDE_DIR}/GL/glew.h" GLEW_4_2 REGEX "^#define GL_VERSION_4_2.*$")
   if (GLEW_4_2)
       set(OPENGL_4_2_FOUND TRUE)
   else ()
       message(WARNING
       "glew-1.7.0 or newer needed for supporting OpenGL 4.2 dependent features"
       )
   endif ()

   file(STRINGS "${GLEW_INCLUDE_DIR}/GL/glew.h" GLEW_4_3 REGEX "^#define GL_VERSION_4_3.*$")
   if (GLEW_4_3)
       SET(OPENGL_4_3_FOUND TRUE)
   else ()
       message(WARNING
       "glew-1.9.0 or newer needed for supporting OpenGL 4.3 dependent features"
       )
   endif ()

endif ()

find_package_handle_standard_args(GLEW
    REQUIRED_VARS
        GLEW_INCLUDE_DIR
        GLEW_LIBRARY
)
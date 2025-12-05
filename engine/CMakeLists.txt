file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/**/*.cpp"
)

add_library(kine STATIC ${ENGINE_SOURCES})

target_include_directories(kine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${DREVA_EXTERNAL_INCLUDES}
)

target_link_directories(kine PRIVATE
    ${DREVA_EXTERNAL_LIB_DIRS}
)

target_link_libraries(kine PRIVATE
    raylib
    lua
)

# Linux system libs
if(UNIX AND NOT APPLE)
    target_link_libraries(kine PRIVATE pthread m dl GL)
endif()

# macOS
if(APPLE)
    target_link_libraries(kine PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
        "-framework CoreVideo"
    )
endif()

if (MSVC)
    target_compile_options(kine PRIVATE
        /W4
        /WX
        /permissive-
        /Zc:__cplusplus
    )
else()
    target_compile_options(kine PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
    )
endif()

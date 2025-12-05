file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/**/*.cpp"
)

add_library(dreva_engine STATIC ${ENGINE_SOURCES})

target_include_directories(dreva_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${DREVA_EXTERNAL_INCLUDES}
)

target_link_directories(dreva_engine PRIVATE
    ${DREVA_EXTERNAL_LIB_DIRS}
)

target_link_libraries(dreva_engine PRIVATE
    raylib
    lua
)

# Linux system libs
if(UNIX AND NOT APPLE)
    target_link_libraries(dreva_engine PRIVATE pthread m dl GL)
endif()

# macOS
if(APPLE)
    target_link_libraries(dreva_engine PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
        "-framework CoreVideo"
    )
endif()

# Windows warnings
if(MSVC)
    target_compile_options(dreva_engine PRIVATE /W4 /permissive-)
else()
    target_compile_options(dreva_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

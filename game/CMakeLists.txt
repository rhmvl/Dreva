file(GLOB_RECURSE GAME_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/**/*.cpp"
)

add_executable(Dreva ${GAME_SOURCES})

target_include_directories(Dreva PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Dreva PRIVATE
    kine
)

set_target_properties(Dreva PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Copy assets after build
add_custom_command(
    TARGET Dreva POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_SOURCE_DIR}/bin/assets"
)

if (MSVC)
    target_compile_options(Dreva PRIVATE
        /W4 /WX /permissive- /Zc:__cplusplus
    )
else()
    target_compile_options(Dreva PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wshadow
        -Wunused
    )
endif()

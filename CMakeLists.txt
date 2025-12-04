cmake_minimum_required(VERSION 3.20)
project(Dreva LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build type behavior
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BUILD_SHARED_LIBS OFF)
    message(STATUS "Release: Static linking")
else()
    set(BUILD_SHARED_LIBS ON)
    message(STATUS "Debug: Dynamic linking")
endif()

# External libs
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

set(RAYLIB_DIR             ${EXTERNAL_DIR}/raylib)
set(RAYLIB_INCLUDE_DIR     ${RAYLIB_DIR}/include)
set(RAYLIB_LIB_DIR         ${RAYLIB_DIR}/lib)

set(IMGUI_INCLUDE_DIR      ${EXTERNAL_DIR}/imgui)
set(RLIMGUI_INCLUDE_DIR    ${EXTERNAL_DIR}/rlimgui)

set(GLM_INCLUDE_DIR        ${EXTERNAL_DIR}/glm)
set(ENTT_INCLUDE_DIR       ${EXTERNAL_DIR}/entt)
set(JSON_INCLUDE_DIR       ${EXTERNAL_DIR}/json)
set(STB_INCLUDE_DIR        ${EXTERNAL_DIR}/stb)
set(MINIAUDIO_INCLUDE_DIR  ${EXTERNAL_DIR}/miniaudio)
set(SOL2_INCLUDE_DIR       ${EXTERNAL_DIR}/sol2)
set(LUA_INCLUDE_DIR        ${EXTERNAL_DIR}/lua/include)
set(LUA_LIB_DIR            ${EXTERNAL_DIR}/lua/lib)

# Provide include dirs to subprojects
set(DREVA_EXTERNAL_INCLUDES
    ${RAYLIB_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${RLIMGUI_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${ENTT_INCLUDE_DIR}
    ${JSON_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
    ${MINIAUDIO_INCLUDE_DIR}
    ${SOL2_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}

    ${CMAKE_SOURCE_DIR}/include
)

set(DREVA_EXTERNAL_LIB_DIRS
    ${RAYLIB_LIB_DIR}
    ${LUA_LIB_DIR}
)

add_subdirectory(engine)
add_subdirectory(game)

# ------------------------------------------------------------------------------
# CMake Version
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.6)

# ------------------------------------------------------------------------------
# Project: name and languages
# ------------------------------------------------------------------------------
project(DreamInEngine C CXX)

# ------------------------------------------------------------------------------
# CMake Options
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clang tidy

#set(BUILD_EXECUTABLE ON)
if(BUILD_EXECUTABLE)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
endif()

# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------
add_library(coverage_config INTERFACE)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif()
endif(ENABLE_COVERAGE)

# ------------------------------------------------------------------------------
# Warnings
# ------------------------------------------------------------------------------
add_library(warnings_config INTERFACE)

if(MSVC)
    target_compile_options(warnings_config INTERFACE /W4)
else()
    target_compile_options(warnings_config INTERFACE -Wall -std=c++14)
    #target_compile_options(warnings_config INTERFACE -Wall -Wextra -Wpedantic -std=c++14)
endif()

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------
#include_directories(deps) # include deps' folder. Note that you could include ${some_dep_include_dirs} from deps folder in order to be more precise at folder inclusion.
include_directories(deps/externals/glad/include)
#include_directories(deps/externals/assimp/include)
include_directories(deps/externals/glfw_3.2.1/include) # TODO: self include this to target ?
include_directories(deps/externals/googletest/googletest/include)
include_directories(deps/externals/googletest/googlemock/include)
include_directories(src)
#include_directories(assets)

include_directories(deps/externals/stb/include)

set(BOX2D_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/externals/Box2D)
set(GLM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/externals/glm_0.9.9.3)
set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/externals/imgui-1.68/include)
set(SOIL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/externals/soil/include)

include_directories(${BOX2D_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${IMGUI_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})

# ------------------------------------------------------------------------------
# Dependencies (+ externals)
# ------------------------------------------------------------------------------
add_subdirectory(deps)

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
add_subdirectory(src)

# ------------------------------------------------------------------------------
# Assets
# ------------------------------------------------------------------------------
add_subdirectory(assets)

# ------------------------------------------------------------------------------
# CTest -> testing
# ------------------------------------------------------------------------------
option (BUILD_TESTING "Build the testing tree." ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    include(CTest)
    add_subdirectory(tests)
endif()
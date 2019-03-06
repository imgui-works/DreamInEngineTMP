set(PROJECT_SOURCE_FILES complex.cpp)

add_library(project_src_lib ${PROJECT_SOURCE_FILES})

target_include_directories(project_src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # Note: see if it includes .hpp && .cpp OR only .cpp files

target_link_libraries(project_src_lib PUBLIC coverage_config warnings_config) # Include code-coverage & warnings settings

# ------------------------------------------------------------------------------
# Modules
# ------------------------------------------------------------------------------
add_library(core
        GLFWEnvironment.h
        GLFWEnvironment.cpp
        SpriteRenderer.h
        SpriteRenderer.cpp
        ResourceManager.h
        ResourceManager.cpp)
# TODO: target_include directories with PRIVATE specifier => Enable "secured && private" includes for each module.

# ------------------------------------------------------------------------------
# Modules
# ------------------------------------------------------------------------------
add_subdirectory(components)
add_subdirectory(entities)
add_subdirectory(events)
add_subdirectory(HUD)
add_subdirectory(scenes)
add_subdirectory(systems)
add_subdirectory(utils)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
file(GLOB ch ${CMAKE_CURRENT_SOURCE_DIR}/components/*.h)
file(GLOB cs ${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp)
file(GLOB eh ${CMAKE_CURRENT_SOURCE_DIR}/entities/*.h)
file(GLOB es ${CMAKE_CURRENT_SOURCE_DIR}/entities/*.cpp)
file(GLOB evh ${CMAKE_CURRENT_SOURCE_DIR}/events/*.h)
file(GLOB evs ${CMAKE_CURRENT_SOURCE_DIR}/events/*.cpp)
#file(GLOB hudh ${CMAKE_CURRENT_SOURCE_DIR}/HUD/*.h)
#file(GLOB huds ${CMAKE_CURRENT_SOURCE_DIR}/HUD/*.cpp)
file(GLOB sh ${CMAKE_CURRENT_SOURCE_DIR}/scenes/*.h)
file(GLOB ss ${CMAKE_CURRENT_SOURCE_DIR}/scenes/*.cpp)
file(GLOB syh ${CMAKE_CURRENT_SOURCE_DIR}/systems/*.h)
file(GLOB sys ${CMAKE_CURRENT_SOURCE_DIR}/systems/*.cpp)
file(GLOB uh ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h)
file(GLOB us ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp)

add_executable(DreamInEngine mainX.cpp ${PROJECT_SOURCE_DIR}/deps/externals/soil/include/soil/soil.h GLFWEnvironment.h GLFWEnvironment.cpp ResourceManager.h ResourceManager.cpp SpriteRenderer.h SpriteRenderer.cpp ${ch} ${cs} ${eh} ${es} ${evh} ${evs} ${hudh} ${huds} ${sh} ${ss} ${syh} ${sys} ${uh} ${us})

# TODO: create an ECS lib
# TODO: link the ECS lib ??

# TODO:

#target_link_libraries(DreamInEngine PRIVATE project_src_lib scenes systems HUD core events components entities utils imgui glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb Box2D soil -lstdc++fs)
target_link_libraries(DreamInEngine PRIVATE project_src_lib core soil glfw ${GLFW_LIBRARIES} glad ${GLAD_LIBRARIES} glm stb Box2D -lstdc++fs)

if (MSVC)
    target_compile_definitions(DreamInEngine PRIVATE mainX=main MSVC_PLATFORM)
else ()
    target_compile_definitions(DreamInEngine PRIVATE mainX=main)
endif ()
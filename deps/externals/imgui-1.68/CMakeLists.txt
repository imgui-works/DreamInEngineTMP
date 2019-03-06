project(imgui)

file(GLOB IMGUI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui/*.h)
file(GLOB IMGUI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} ${IMGUI_SOURCES} ${IMGUI_HEADERS})

#target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_HEADERS})
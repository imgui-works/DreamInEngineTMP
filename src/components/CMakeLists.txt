project(components)

file(GLOB COMPONENTS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB COMPONENTS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${COMPONENTS_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${COMPONENTS_HEADERS})

target_link_libraries(${PROJECT_NAME} Box2D) # enable access to Box2D
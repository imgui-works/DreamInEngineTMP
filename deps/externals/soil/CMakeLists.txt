# ------------------------------------------------------------------------------
# SOIL
# ------------------------------------------------------------------------------
project(soil) #Note: The glad version currently in use is the glad compatibility version 3.3

# ------------------------------------------------------------------------------
# SOIL library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/deps/externals/soil/include")
#----------------------------- CREATE LIBRARY -----------------------------#

cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME bukhtagram_mc_server)
project(${PROJECT_NAME})

add_library(
    ${PROJECT_NAME}
    INTERFACE
)

#----------------------------- LINK LIBRARIES -----------------------------#

add_subdirectory(Models)
add_subdirectory(Controllers)

set(
    ALL_LIBS
    bukhtagram_mc_server_models
    bukhtagram_mc_server_controllers
)

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    ${ALL_LIBS}
)
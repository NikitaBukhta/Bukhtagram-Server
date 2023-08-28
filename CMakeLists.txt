#--------------------------- MAIN CONFIGURATION ---------------------------#

cmake_minimum_required(VERSION 3.6.0)
set(PROJECT_NAME bukhtagram_server)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(
    ${PROJECT_NAME}
    ${CPP_SOURCES}
)

#----------------------------- LINK LIBRARIES -----------------------------#

add_subdirectory(Server)

set(
    ALL_LIBS
    bukhtagram_mc_server
)

target_link_libraries(
    ${PROJECT_NAME}
    ${ALL_LIBS}
)
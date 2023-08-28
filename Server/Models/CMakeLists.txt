#----------------------------- CONFIGURE CMAKE -----------------------------#

cmake_minimum_required(VERSION 3.25.1)
set(PROJECT_NAME bukhtagram_mc_server_models)
project(${PROJECT_NAME})

#-------------------------------- FUNCTIONS --------------------------------#

# zero elem of RESULT is a output var name;
# addition arg #0 is a head name;
function(get_include_dirs RESULT STARTED_PATH)
    if ("${ARGN}" STREQUAL "")
        list(GET RESULT 0 HEAD)
    else()
        list(GET ARGN 0 HEAD)
    endif()

    file(GLOB FILES RELATIVE ${STARTED_PATH} "${STARTED_PATH}/*")
    foreach (FILE ${FILES})
        if (IS_DIRECTORY "${STARTED_PATH}/${FILE}")
            if (${FILE} MATCHES "include")
                list(APPEND ${HEAD} "${STARTED_PATH}/${FILE}")
            else()
                get_include_dirs(RESULT "${STARTED_PATH}/${FILE}" ${HEAD})
            endif()
        endif()

    endforeach()
    # write found include folder to global HEAD variable. PARENT_SCOPE help to write data to var;
    set(${HEAD} ${${HEAD}} PARENT_SCOPE)
endfunction()

#----------------------------- CREATE LIBRARY -----------------------------#

file(GLOB LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/**/src/*.cpp")

get_include_dirs(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(DIR ${INCLUDE_DIRS})
    message("included dir: ${DIR}")
endforeach()

add_library(
    ${PROJECT_NAME}
    ${LIB_SRC}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIRS}
)

#----------------------------- LINK LIBRARIES -----------------------------#

# Adding Boost library;

find_package(Boost REQUIRED system)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")
message(STATUS "BOOST_SYSTEM: ${BOOST_SYSTEM}")
message(STATUS "BOOST_FILE_SYSTEM: ${BOOST_FILE_SYSTEM}")

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
# if windows compiler;
if(MINGW)
    message(STATUS "MinGW compiler defined!")
    SET(
        WIN_LIBS
        ws2_32
        wsock32
    )
endif()

set(
    ALL_LIBS
    ${Boost_LIBRARIES}
    ${WIN_LIBS}
)

target_link_libraries(
    ${PROJECT_NAME}
    LINK_PUBLIC
    ${ALL_LIBS}
)
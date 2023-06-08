cmake_minimum_required(VERSION 3.20)
project(embedded)

find_program(ECPG ecpg DOC "A precompiler for PostgreSQL embedded code.")
if (${ECPG} STREQUAL "ECPG-NOTFOUND")
    message(FATAL_ERROR "ecpg not found, please install and add to the PATH.")
endif()
find_library(ECPG_LIBARY ecpg DOC "The ECPG library.")


add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ecpg/embedded.c
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/ecpg
    COMMAND ${ECPG} ${ECPG_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/embedded.pgc -o ${CMAKE_CURRENT_BINARY_DIR}/ecpg/embedded.c
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/embedded.pgc
    COMMENT "ECPG Build embedded.pgc"
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

add_executable(esql main.c ${CMAKE_CURRENT_BINARY_DIR}/ecpg/embedded.c)
target_link_libraries(esql ecpg)
target_link_directories(esql PRIVATE ../postgres/src/interfaces/ecpg/ecpglib)
target_include_directories(esql PRIVATE ../postgres/src/interfaces/ecpg/include ../postgres/src/interfaces/libpq ../postgres/src/include)
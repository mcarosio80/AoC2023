cmake_minimum_required(VERSION 3.18.4)

project(AdventOfCode
    LANGUAGES CXX
    VERSION 1.0.2023.1
    DESCRIPTION "Advent of Code C++ repo"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directories
set(AOC_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/input)
set(CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/common)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)


include_directories(${COMMON_DIR})
include_directories(${LIB_DIR}/2023)

find_package(Git REQUIRED)
if(Git_FOUND)
    message("Git found: ${GIT_EXECUTABLE}")
endif()

#Fetch some info to complete metadata
string(TIMESTAMP CURRENT_TS "%Y-%m-%d %H:%M:%S")

execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:"%ad" --date=iso8601 OUTPUT_VARIABLE LAST_COMMIT_DATE)
message("Last commit date: " ${LAST_COMMIT_DATE})
execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:"%an" OUTPUT_VARIABLE LAST_COMMIT_AUTHOR_NAME)
message("Commit author name: " ${LAST_COMMIT_AUTHOR_NAME})
execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:"%H" OUTPUT_VARIABLE LAST_COMMIT_HASH)
message("Last commit hash: " ${LAST_COMMIT_HASH})

configure_file(${CONFIG_DIR}/config.h.in ${COMMON_DIR}/config.h)


# message("Adding subdirectory lib")
# add_subdirectory(lib)
message("Adding subdirectory src")
add_subdirectory(src)
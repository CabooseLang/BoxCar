cmake_minimum_required(VERSION 3.10)

include(cmake/VersionFromGit.cmake)
version_from_git()

project(BoxCar LANGUAGES C ${git_resolved_version})

set(CMAKE_C_STANDARD 11)

file(GLOB lib_source "src/*.c")
file(GLOB lib_header "src/*.h")

add_library(boxcar STATIC ${lib_source})
add_executable(bc src/app/main.c ${lib_source} ${lib_header})
target_link_libraries(bc caboose)
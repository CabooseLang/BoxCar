cmake_minimum_required(VERSION 3.10)

include(cmake/VersionFromGit.cmake)
include(cmake/ClangFormat.cmake)

version_from_git()
project(BoxCar LANGUAGES C VERSION ${git_resolved_version})
set(CMAKE_C_STANDARD 11)

file(GLOB lib_source "src/*.c")
file(GLOB lib_header "src/*.h")

configure_file(src/version.h.in version.h)

add_library(boxcar STATIC ${lib_source})
add_executable(bc src/app/main.c ${lib_source} ${lib_header})

target_include_directories(bc PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(bc boxcar)
target_clangformat_setup(bc)

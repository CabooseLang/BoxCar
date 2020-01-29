cmake_minimum_required(VERSION 3.10)

include(cmake/VersionFromGit.cmake)
include(cmake/ClangFormat.cmake)

version_from_git()
project(BoxCar LANGUAGES C VERSION ${git_resolved_version})
set(CMAKE_C_STANDARD 11)

file(GLOB main_source "src/*.c")
file(GLOB main_header "src/*.h")

file(GLOB dep_misc_source "src/libs/*.c")
file(GLOB dep_misc_header "src/libs/*.h")

set(lib_sources ${main_source} ${main_header} ${dep_misc_header} ${dep_misc_source})

configure_file(src/version.h.in version.h)

add_library(boxcar STATIC ${lib_sources})
add_executable(bc src/app/main.c ${lib_sources})

target_include_directories(bc PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(bc boxcar)
target_clangformat_setup(bc)

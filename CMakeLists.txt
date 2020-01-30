cmake_minimum_required(VERSION 3.10)

include(cmake/VersionFromGit.cmake)
include(cmake/ClangFormat.cmake)

version_from_git()
project(BoxCar LANGUAGES CXX VERSION ${git_resolved_version})

file(GLOB main_source "src/*.cpp" "src/*.c")
file(GLOB main_header "src/*.hpp" "src/*.h")

set(lib_sources ${main_source} ${main_header})

configure_file(src/version.h.in version.h)

FIND_PACKAGE(Boost 1.67 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(boxcar STATIC ${lib_sources})
target_link_libraries(boxcar LINK_PUBLIC ${Boost_LIBRARIES})

add_executable(bc src/app/main.cpp ${lib_sources})
target_include_directories(bc PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(bc boxcar)
target_clangformat_setup(bc)

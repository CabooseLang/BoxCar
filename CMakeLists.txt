cmake_minimum_required(VERSION 3.10)

include(cmake/VersionFromGit.cmake)
include(cmake/ClangFormat.cmake)

version_from_git()
project(BoxCar LANGUAGES CXX VERSION ${git_resolved_version})

file(GLOB main_source "src/*.cpp" "src/*.c")
file(GLOB main_header "src/*.hpp" "src/*.h")

file(GLOB_RECURSE server_source "src/server/**/*.cpp" "src/server/**/*.c")
file(GLOB_RECURSE server_header "src/server/**/*.hpp" "src/server/**/*.h")

set(server_sources "src/server/main.cpp" ${server_source} ${server_header})
set(main_sources ${main_source} ${main_header})

configure_file(src/version.h.in version.h)

find_package(Threads)
find_package(Boost 1.67 COMPONENTS program_options regex system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(boxcar STATIC ${main_sources})
target_link_libraries(boxcar LINK_PUBLIC ${Boost_LIBRARIES})

add_executable(bc src/app/main.cpp ${main_sources})
target_include_directories(bc PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(bc boxcar)
target_clangformat_setup(bc)

add_executable(bc-server ${server_sources} ${main_sources})
target_include_directories(bc-server PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(bc-server boxcar ${CMAKE_THREAD_LIBS_INIT})

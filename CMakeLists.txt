# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("jabmpt-pp")

# Include sub-projects.
add_subdirectory ("src")
file(COPY "test/Hallway.bmp" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/test")

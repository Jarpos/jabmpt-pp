# CMakeList.txt : CMake project for jabmpt-pp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable(jabmpt-pp
    "main.cpp"

    "images/bmp.cpp"
    "images/png.cpp"
    "images/image.cpp"

    "transforms/blackwhite.cpp"
    "transforms/blur.cpp"
    "transforms/channels.cpp"
    "transforms/flip.cpp"
    "transforms/edgedetection.cpp"
    "transforms/invert.cpp"
)

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET jabmpt-pp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

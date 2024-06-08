# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define project name
project(opencv_mplane)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Declare the executable target built from your sources
add_executable(opencv_mplane_mmap main.cpp v4ldevice.cpp)
add_executable(opencv_mplane_dma_heap main.cpp v4ldevice_dmaheap.cpp)

# Link your application with OpenCV libraries
target_link_libraries(opencv_mplane_mmap ${OpenCV_LIBS})
target_link_libraries(opencv_mplane_dma_heap ${OpenCV_LIBS})

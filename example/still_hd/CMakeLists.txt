cmake_minimum_required(VERSION 2.8)

project(still)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
  message(STATUS "OpenCV library status:")
  message(STATUS "    config: ${OpenCV_DIR}")
  message(STATUS "    version: ${OpenCV_VERSION}")
  message(STATUS "    libraries: ${OpenCV_LIBS}")
  message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
  include_directories(${OpenCV_INCLUDE_DIRS})

  add_executable(still main.cpp)

  target_link_libraries(still ${OpenCV_LIBS})
endif(OpenCV_FOUND)

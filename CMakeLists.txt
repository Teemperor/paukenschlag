cmake_minimum_required(VERSION 3.3)
project(shooter)

# Enable C++11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

find_package(Threads)

# External data
include_directories(extern/)

# Normal sources
include_directories(src/)
file(GLOB_RECURSE SRC_LIST src/*.cpp )
add_library(CORE ${SRC_LIST})

# Testing
enable_testing()

file(GLOB TEST_FILES "tests/*.cpp")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(BASENAME ${TEST_FILE} NAME_WE)
    add_executable(${BASENAME} ${TEST_FILE})
    target_link_libraries(${BASENAME} CORE ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} Box2D)

    add_test(${BASENAME} ${BASENAME})
endforeach()

# Normal executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} CORE ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} Box2D)

install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION share/${PROJECT_NAME})

# Copying data files
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
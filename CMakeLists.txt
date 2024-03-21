cmake_minimum_required(VERSION 3.0)

project(synthetix VERSION 1.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    src/synthetix.cpp
    src/parser.cpp
    src/pattern.cpp
    src/block.cpp
    src/comment-parser.cpp
    src/metadata-parser.cpp
    src/sequence-parser.cpp
    src/scoped-timer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME})
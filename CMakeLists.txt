cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(opc_test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

set(AWS_INSTALL_PATH ${PROJECT_BINARY_DIR}/app/$<CONFIG>)

add_subdirectory(app)

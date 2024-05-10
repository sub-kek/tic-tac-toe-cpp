cmake_minimum_required(VERSION 3.28)

project(tictactoe LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE tictactoe_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE tictactoe_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (tictactoe_INCLUDE_DIRS "")
foreach (_headerFile ${tictactoe_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND tictactoe_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES tictactoe_INCLUDE_DIRS)

add_executable(tictactoe ${tictactoe_SOURCES})
target_include_directories(tictactoe PRIVATE ${tictactoe_INCLUDE_DIRS})
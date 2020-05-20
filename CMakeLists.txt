cmake_minimum_required(VERSION 3.16)
project(2DGameEngine)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES
        2DGameEngine/*.cpp)


set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/include")
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64/SDL2main.lib;${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64/SDL2_image.lib;")

#set(LUA_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/lua")
#set(LUA_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/extern/lua/lua53.lib")

include_directories(${SDL2_INCLUDE_DIR})
add_executable(2DGameEngine ${SRC_FILES})
target_link_libraries(2DGameEngine ${SDL2_LIBRARIES})
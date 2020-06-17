cmake_minimum_required(VERSION 3.16)
project(2DGameEngine)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES
        2DGameEngine/*.cpp
        2DGameEngine/*.h)

if(APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    if(SDL2_FOUND)
        message(STATUS "SDL FOUND")
    endif(SDL2_FOUND)
    find_package(SDL2_image REQUIRED)

    if(SDL2_image_FOUND)
        message(STATUS "SDL_image FOUND")
    endif(SDL2_image_FOUND)

    message(STATUS ${SDL2_LIBRARIES})
    set(SDL_IMAGE_LIBS -L/usr/local/Cellar/sdl2_image/2.0.5/lib -lSDL2_image)
    add_executable(2DGameEngine ${SRC_FILES})

    find_package(LUA REQUIRED)

    if(LUA_FOUND)
        message(STATUS "Lua Found")
    endif(LUA_FOUND)

    set(LUA_BRIDGE_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/LuaBridge")

    include_directories(extern)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS} ${LUA_BRIDGE_DIR})
    target_link_libraries(2DGameEngine ${SDL2_LIBRARIES} ${SDL_IMAGE_LIBS} ${LUA_LIBRARIES})
endif(APPLE)

if(WIN32)
set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/include")
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64/SDL2main.lib;${CMAKE_CURRENT_LIST_DIR}/extern/SDL2/lib/x64/SDL2_image.lib;")

set(LUA_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/lua")
set(LUA_LIBS "${CMAKE_CURRENT_LIST_DIR}/extern/lua/lua53.lib")

include_directories(extern)

set(LUA_BRIDGE_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/LuaBridge")

include_directories(${SDL2_INCLUDE_DIR} ${LUA_INCLUDE_DIR} ${LUA_BRIDGE_DIR})
add_executable(2DGameEngine ${SRC_FILES} 2DGameEngine/MouseControlComponent.cpp 2DGameEngine/MouseControlComponent.h 2DGameEngine/InputManager.cpp 2DGameEngine/InputManager.h 2DGameEngine/CursorComponent.cpp 2DGameEngine/CursorComponent.h 2DGameEngine/WorldManager.cpp 2DGameEngine/WorldManager.h)
target_link_libraries(2DGameEngine ${SDL2_LIBRARIES} ${LUA_LIBS})
endif(WIN32)
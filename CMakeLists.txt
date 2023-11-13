cmake_minimum_required(VERSION 3.25)
project(Dungeon-Descent)

set(CMAKE_CXX_STANDARD 14)

set(SDL_INCLUDE_DIR "C:/SDL2/include")
set(SDL_LIBRARY_DIR "C:/SDL2/lib/x86")

include_directories(${SDL_INCLUDE_DIR})
link_directories(${SDL_LIBRARY_DIR})

add_executable(Dungeon-Descent src/main.cpp include/renderer.hpp include/utils.hpp include/constants.hpp src/renderer.cpp src/game.cpp include/level.hpp src/level.cpp include/vector.hpp include/entity.hpp src/player.cpp include/player.hpp include/tile_info.hpp include/tile_info.hpp include/tile_info.hpp src/utils.cpp include/event_manager.hpp src/event_manager.cpp include/weapon.hpp src/weapon.cpp include/json.hpp src/json.cpp)

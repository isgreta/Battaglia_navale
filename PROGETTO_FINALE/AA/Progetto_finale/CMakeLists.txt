cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(Progetto_finale)

include_directories(include)

add_library(Game
	include/Game.h
	src/Game.cpp
)

add_library(Helper
	include/Helper.h
	src/Helper.cpp
)

add_library(Radar
	include/Radar.h
	src/Radar.cpp
)

add_library(Bot
	include/Bot.h
	src/Bot.cpp
)

add_executable(battaglia_navale
	src/battaglia_navale.cpp
)

add_executable(replay
	src/replay.cpp
)

target_link_libraries(battaglia_navale
	Bot
	Game
	Helper 
	Radar
)

target_link_libraries(replay
	Bot
	Game
	Helper 
	Radar
)


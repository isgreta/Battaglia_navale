cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(Progetto_finale)

include_directories(include)

add_library(Battaglia
	include/Battaglia.h
	src/Battaglia.cpp
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

add_executable(main 
	src/main.cpp
)

target_link_libraries(main 
	Bot
	Battaglia
	Helper 
	Radar
)

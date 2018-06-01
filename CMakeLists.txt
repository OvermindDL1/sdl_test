cmake_minimum_required(VERSION 3.5)
include("cmake/HunterGate.cmake")
HunterGate(
	URL "https://github.com/ruslo/hunter/archive/v0.21.13.tar.gz"
	SHA1 "331bf20601aed3369e1d00388d08af8169b2e6c2"
	LOCAL
)

project(sdl-test)

hunter_add_package(SDL2)
hunter_add_package(SDL_image)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL_image CONFIG REQUIRED)

add_executable(sdl-test
	src/Game.cpp

	src/ai/Player.cpp
	src/ai/Zombie.cpp

	src/graphics/Texture.cpp
)

target_compile_features(sdl-test PRIVATE cxx_std_14)

target_link_libraries(sdl-test
	SDL2::SDL2
	SDL_image::SDL_image
)


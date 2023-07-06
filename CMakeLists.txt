cmake_minimum_required(VERSION 3.23)
project(Some_Game)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSFML_STATIC)

include_directories("SFML/include/")
link_directories("SFML/lib/")

include_directories("include/")

add_executable(Some_Game main.cpp
		include/engine.h src/engine.cpp
		include/menu.h src/menu.cpp
		include/game.h src/game.cpp
		include/game_data.h src/game_data.cpp
		include/Logger.h include/pch.h

)

	
target_link_libraries(Some_Game
					    debug sfml-graphics-s-d 
						debug sfml-window-s-d
						debug sfml-system-s-d
						debug sfml-audio-s-d)
						
target_link_libraries(Some_Game 
					    optimized sfml-graphics-s 
						optimized sfml-window-s
						optimized sfml-system-s
						optimized sfml-audio-s)
	
target_link_libraries(Some_Game opengl32 freetype winmm gdi32 openal32 flac vorbisenc vorbisfile vorbis ogg)

file(COPY "assets" DESTINATION "/")
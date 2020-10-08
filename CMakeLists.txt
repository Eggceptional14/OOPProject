cmake_minimum_required(VERSION 3.15)
project(Space_Invader)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "./SFML/inlude")
set(SFML_LIBRARY_DIR "./SFML/build/lib")

add_executable(Space_Invader Source/Main/main.cpp Source/Game/Entity/Player.hpp Source/Game/Entity/Alien.hpp Source/Game/Collidable.hpp Source/Game/Collidable.cpp Source/Main/MGame.hpp Source/Utility/GameState/GameState.hpp Source/Utility/GameState/GameState.cpp Source/Utility/Resources/ResHolder.hpp Source/Utility/Resources/ResHolder.cpp Source/Utility/Resources/ResManager.hpp Source/Game/Renderer/LRenderer.hpp Source/Game/Renderer/LRenderer.cpp Source/Game/Renderer/Animation.hpp Source/Game/Renderer/Animation.cpp Source/Game/Entity/Player.cpp Source/Game/DispInform.hpp Source/Game/Entity/UFO.hpp Source/Game/Entity/Explosion.hpp Source/Game/Entity/Projectile.hpp Source/Game/Entity/Barrier.hpp Source/Game/Entity/Explosion.cpp Source/Game/Entity/Projectile.cpp Source/Utility/Extra/Random.hpp Source/Game/Entity/UFO.cpp Source/Game/Entity/Alien.cpp Source/Game/Map.hpp Source/Game/AlienManager.hpp Source/Game/AlienManager.cpp Source/Game/Map.cpp Source/Game/Entity/Barrier.cpp Source/Game/State/Playing.hpp Source/Game/State/MainMenu.hpp Source/Main/MGame.cpp Source/Game/State/Playing.cpp Source/Utility/GUI/Widget.hpp Source/Utility/GUI/Widget.cpp Source/Utility/GUI/Button.cpp Source/Utility/GUI/Button.hpp Source/Game/State/GameOver.cpp Source/Game/State/GameOver.hpp Source/Game/State/MainMenu.cpp Source/Utility/Extra/Score.cpp Source/Utility/Extra/Score.hpp)


link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(Space_Invader sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

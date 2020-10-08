#ifndef SPACE_INVADER_RESHOLDER_HPP
#define SPACE_INVADER_RESHOLDER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResManager.hpp"

using namespace std;

/*
 * Class that holds data of every resources needs by the game
 */

class ResourceHolder : public sf::NonCopyable {
public:
    static ResourceHolder& get();
    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::SoundBuffer> sound_buffers;

private:
    ResourceHolder(); //initialize each resources with its own folder name and extension
};

#endif

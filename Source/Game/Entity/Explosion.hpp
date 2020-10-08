#ifndef SPACE_INVADER_EXPLOSION_HPP
#define SPACE_INVADER_EXPLOSION_HPP

#include <SFML/Graphics.hpp>

namespace SI {

    class Explosion {
    public:
        Explosion( const sf::Vector2f& pos );

        bool isOver() const; //return true if the effect of explosion exceed the time limit

        const sf::Vector2f& getPosition() const; //return position of explosion as vector2f object

    private:
        sf::Vector2f ex_position;  //Position of explosion effect
        sf::Clock ex_lifetime;     //Life time of explosion
    };
}

#endif

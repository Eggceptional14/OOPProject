#ifndef SPACE_INVADER_COLLIDABLE_HPP
#define SPACE_INVADER_COLLIDABLE_HPP

#include "SFML/Graphics.hpp"

using namespace std;

namespace SI {

    /*
     * Base class for all collidable object
     */

    class Collidable {
    public:
        Collidable( float width, float height );

        bool tryCollide(Collidable &other); //check for collision
        sf::FloatRect getBox() const; //get object size

        virtual const sf::Vector2f& getPosition() const = 0; //return const of vector2f object
        virtual void onCollide(Collidable &other ) = 0; //what to do when collide with another projectile

    private:
        sf::Vector2f size;
    };

}

#endif

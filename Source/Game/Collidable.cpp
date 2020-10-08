#include "Collidable.hpp"

namespace SI {

    Collidable::Collidable( float width, float height )
    : size( width, height ) {
    }

    bool Collidable::tryCollide( Collidable &other ) {
        //check for box intersection with other object
        if ( getBox().intersects( other.getBox() ) ) {
            onCollide(other);
            other.onCollide(*this);
            return true;
        }
        return false;
    }

    sf::FloatRect Collidable::getBox() const {

        return {
            getPosition().x, getPosition().y, size.x, size.y
        };
    }
}
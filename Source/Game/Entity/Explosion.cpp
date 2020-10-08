#include "Explosion.hpp"

namespace SI {

    Explosion::Explosion(const sf::Vector2f &pos)
    :ex_position( pos ) {
    }

    bool Explosion::isOver() const {
        //return true if lifetime of animation is over
        return ex_lifetime.getElapsedTime().asSeconds() >= 0.2f;
    }

    const sf::Vector2f& Explosion::getPosition() const {
        return ex_position;
    }

}
#include "Alien.hpp"

namespace SI {

    Alien::Alien(const sf::Vector2f &initLocation, SI::Alien::Type type)
    : Collidable( WIDTH, HEIGHT ), a_initialPos( initLocation ), a_location( initLocation ), a_type( type ){
    }

    void Alien::move(float x, float y) {
        a_location += { x, y };
    }

    const sf::Vector2f& Alien::getPosition() const {
        return a_location;
    }

    bool Alien::isAlive() const {
        return a_isAlive;
    }

    Alien::Type Alien::getType() const {
        return a_type;
    }

    void Alien::onCollide(Collidable &other) {
        a_isAlive = false;
    }

    void Alien::makeAlive() {
        a_isAlive = true;
        a_location = a_initialPos;
    }
}
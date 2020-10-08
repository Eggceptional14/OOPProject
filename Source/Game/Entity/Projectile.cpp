#include "Projectile.hpp"
#include "../DispInform.hpp"

namespace SI {

    Projectile::Projectile(const sf::Vector2f &pos, SI::Projectile::Type type, SI::Projectile::Direction dir)
    : Collidable( WIDTH / 1.5, HEIGHT ), p_position( pos ), p_type( type ), p_direction( dir ){
    }

    void Projectile::update(float dt) {
        float speed = 650 * (float)p_direction * dt;
        p_position.y += speed; //change position by speed

        if( p_position.y <= 0 || p_position.y >= Display::HEIGHT )
            destroy();
    }

    void Projectile::onCollide(Collidable &other) {
        destroy();
    }

    void Projectile::destroy() {
        p_isActive = false;
    }

    const sf::Vector2f& Projectile::getPosition() const {
        return p_position;
    }

    bool Projectile::isActive() const {
        return p_isActive;
    }

    Projectile::Type Projectile::getType() const {
        return p_type;
    }

    Projectile::Direction Projectile::getDirection() const {
        return p_direction;
    }

    int Projectile::getOwner() const {
        return p_Owner;
    }
}
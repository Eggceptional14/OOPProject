#ifndef SPACE_INVADER_PROJECTILE_HPP
#define SPACE_INVADER_PROJECTILE_HPP

#include <SFML/Graphics.hpp>

#include "../Collidable.hpp"

using namespace std;

namespace SI {

    class Projectile : public Collidable {
    public:
        constexpr static float WIDTH = 12;
        constexpr static float HEIGHT = 24;

        enum class Type //Style of projectile
        {
            Bullet, //type of projectile use by player

            //projectile use by enemy
            Lightning,
            Knife
        };

        enum class Direction //Direction of projection ( from enemy : down, player : up )
        {
            Up = -1, //projectile going upward
            Down = 1 //projectile going downward
        };

        Projectile( const sf::Vector2f& pos, Type type, Direction dir );
        void update( float dt ); //update projectile
        void onCollide( Collidable& other ) override; //action after projectile collide with another object
        void destroy(); //Destroy projectile on hit with another collidable object

        const sf::Vector2f& getPosition() const override; //return vector2f position of projectile
        bool isActive() const; //return true if projectile is active on the screen
        Type getType() const; //return type of projectile
        Direction getDirection() const; //return direction of projectile

        int getOwner() const; //return owner of the projectile ( use in collision )

    private:
        sf::Vector2f p_position;
        bool p_isActive = true;
        int p_Owner;
        Type p_type;
        Direction p_direction;
    };
}

#endif

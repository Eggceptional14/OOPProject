#ifndef SPACE_INVADER_ALIEN_HPP
#define SPACE_INVADER_ALIEN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../Collidable.hpp"

using namespace std;

namespace SI {

    class Alien : public Collidable {
    public:
        //size of alien
        constexpr static float WIDTH = 48;
        constexpr static float HEIGHT = 32;

        enum class Type //Types of aliens (name come from wiki)
        {
            Crab,
            Octopus,
            Squid
        };

        Alien( const sf::Vector2f& initLocation, Type type );

        void move( float x, float y ); //move alien towards player

        const sf::Vector2f& getPosition() const override; //get position of alien
        bool isAlive() const; //get living status of alien
        Type getType() const; //get type of alien

        void onCollide( Collidable& other ) override; //action when alien collide with another object

        void makeAlive(); //make alien alive

    private:
        const sf::Vector2f a_initialPos; //stating position of an alien
        sf::Vector2f a_location; //location of alien in the map
        bool a_isAlive = false; //living status
        Type a_type; //type of alien
    };
}
#endif

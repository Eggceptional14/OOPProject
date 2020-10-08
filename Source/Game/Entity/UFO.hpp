#ifndef SPACE_INVADER_UFO_HPP
#define SPACE_INVADER_UFO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../Collidable.hpp"
#include "../Renderer/Animation.hpp"
#include "../../Utility/Extra/Random.hpp"

namespace SI {

    class UFO : public Collidable {
    public:
        enum class Status //status of ufo
        {
            Waiting, //stay still
            Flying, //moving along screen
            Destroyed //hit by projectile
        };

        UFO( Random<>& rand );

        Status getStatus() const; //return status of ufo

        void update( float dt ); //update ufo frame by frame
        void draw( sf::RenderTarget& window ); //render ufo

        const sf::Vector2f& getPosition() const override; //return vector2f position of ufo
        void onCollide( Collidable& other ) override; //when collide with projectile

    private:
        Random<>& n_rng;
        float u_velX;

        Status u_status;
        Animation u_animation;

        sf::RectangleShape u_sprite;

        sf::Sound u_sound;
    };
}

#endif

#ifndef SPACE_INVADER_PLAYER_HPP
#define SPACE_INVADER_PLAYER_HPP

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "../Collidable.hpp"
#include "../Renderer/Animation.hpp"

namespace SI {

    class Player : public Collidable{
    public:
        constexpr static int WIDTH = 44;
        constexpr static int HEIGHT  = 32;

        Player();

        void input(); //receive event from user
        void update( float dt ); //update character
        void draw( sf::RenderTarget& target ); //render player sprite

        sf::Vector2f gunPos() const; //get gun's coordinate
        const sf::Vector2f& getPosition() const override; //get player's coordinate

        void onCollide(Collidable& other ) override; //do when collide with other projectile

        int getLives() const; //get player's current health
        bool isAlive() const; //return false is player got shot

        void revive(); //try revive player if no health remaining reviving will not happen

    private:
        void restart(); //Restart the player after got shot

        sf::RectangleShape p_sprite;
        sf::Vector2f p_velocity;
        sf::Clock p_deathTimer;
        Animation p_deathAnimation;

        sf::Sound p_deathSound;

        bool p_isalive = true;
        int p_health = 3;
    };

}

#endif

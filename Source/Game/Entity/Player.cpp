#include "Player.hpp"
#include "../../Utility/Resources/ResHolder.hpp"
#include "../DispInform.hpp"

namespace SI {

    const float BASE_Y = (float)Display::HEIGHT - 40.0f;

    Player::Player()
    : Collidable( WIDTH, HEIGHT ), p_deathAnimation(11, 8 ) {
        //set player sprite properties
        p_sprite.setSize({WIDTH, HEIGHT } );
        p_sprite.setPosition((float)Display::WIDTH / 2, BASE_Y );
        p_sprite.setTexture(&ResourceHolder::get().textures.get("player" ) );
        p_sprite.setTextureRect({0, 0, 11, 8 } );

        //add death animation
        for( int i = 0; i < 20; i++ )
            p_deathAnimation.addFrame(( (i % 2 ) + 1 ), sf::seconds(0.1f ) );

        //set sound
        p_deathSound.setBuffer(ResourceHolder::get().sound_buffers.get("explosion" ) );
    }

    void Player::input() {
        using KEY = sf::Keyboard::Key; //macro
        auto keyDown = []( sf::Keyboard::Key k ) { //lambda function for key pressed
            return sf::Keyboard::isKeyPressed( k );
        };

        float speed = 20.0;
        if ( keyDown( KEY::A ) ) //move left when press a
            p_velocity.x -= speed;
        else if ( keyDown( KEY::D ) ) //move right when press d
            p_velocity.x += speed;
    }

    void Player::update(float dt) {
        if( p_isalive ) {
            auto w = p_sprite.getGlobalBounds().width; //bounding rectangle of entity
            p_sprite.move(p_velocity * dt ); // move sprite
            p_velocity *= 0.95f;
            if(p_sprite.getPosition().x <= 0 ) { //if character went through 0 ( left most side of display )
                p_velocity.x = 1.0f;
                p_sprite.setPosition(1.0f, BASE_Y ); // set position so sprite won't pass display boundary
            }
            else if(p_sprite .getPosition().x >= Display::WIDTH ) {//if character goes through further than display width
                p_velocity.x = -1.0f;
                // set position so sprite won't pass display boundary
                p_sprite.setPosition(Display::WIDTH - 1.0f - w, BASE_Y );
            }
        }
    }

    void Player::draw(sf::RenderTarget &target) {
        if ( !p_isalive ) {  //if player died
            p_sprite.setTextureRect(p_deathAnimation.getFrame() ); //set death texture
        }
        if( p_health >= 0 ) {
            target.draw(p_sprite ); //draw sprite of character
        }
    }

    sf::Vector2f Player::gunPos() const {
        return { //return gun position
                p_sprite.getPosition().x + p_sprite.getGlobalBounds().width / 2,
                p_sprite.getPosition().y
        };
    }

    const sf::Vector2f& Player::getPosition() const {
        return p_sprite.getPosition();
    }

    void Player::onCollide(Collidable &other) {
        p_isalive = false;
        p_deathTimer.restart();
        p_deathSound.play();
    }

    int Player::getLives() const {
        return p_health;
    }

    bool Player::isAlive() const {
        return p_isalive;
    }

    void Player::revive() {
        if (p_deathTimer.getElapsedTime().asSeconds() >= 1.5f )
            restart();
    }

    void Player::restart() {
        p_velocity *= 0.0f;
        p_sprite.setTextureRect({0, 0, 11, 8 } );
        p_isalive = true;
        p_health -= 1;
        p_sprite.setPosition({Display::WIDTH / 2, BASE_Y } );
    }
}

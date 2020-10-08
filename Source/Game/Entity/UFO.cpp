#include "UFO.hpp"

#include "../DispInform.hpp"
#include "../../Utility/Resources/ResHolder.hpp"

namespace SI {

    const float WIDTH = 72;
    const float HEIGHT = 36;
    const float Y_POS = 45; //base y position of ufo

    UFO::UFO(Random<> &rand)
        :Collidable( WIDTH, HEIGHT ), n_rng( rand ), u_animation( 16, 8 ) {

        //set sprite property
        u_sprite.setSize( { WIDTH, HEIGHT } );
        u_sprite.setPosition( (float)Display::WIDTH, Y_POS );
        u_sprite.setTexture( &ResourceHolder::get().textures.get("ufo" ) );

        //add ufo animation frame
        for( int i = 0; i < 3; i++ )
            u_animation.addFrame( i, sf::seconds( 0.2f ) );

        //set ufo sound
        u_sound.setBuffer( ResourceHolder::get().sound_buffers.get( "ufo_lowpitch" ) );
        u_sound.setVolume( 8 );
    }

    UFO::Status UFO::getStatus() const {
        return u_status;
    }

    void UFO::update(float dt) {
        //Update each status diferrently
        switch( u_status ) {
            case Status::Waiting :
                if( n_rng.getIntinRange(1, 250 ) == 100 ) { //random number get 100 will start ufo movement
                    u_status = Status::Flying;
                    //velx < 0 ufo will move left side
                    //velx >= 0 ufo will move right side
                    u_velX = (float)n_rng.getIntinRange( -1, 1 ) * 200.0f;
                    float x_pos;
                    if( u_velX >= 0 ) { //ufo starting position at left side of the window
                        x_pos = -WIDTH;
                    }
                    else { //ufo starting position at right side of window
                        x_pos = Display::WIDTH;
                    }
                    u_sprite.setPosition( x_pos, Y_POS );
                }
                break;

            case Status::Flying :
                u_sprite.move( u_velX * dt, 0 ); //velX * dt is speed of ufo

                //ufo out of window bound
                if ( getPosition().x <= -WIDTH || getPosition().x >= Display::WIDTH + WIDTH ) {
                    u_status = Status::Waiting;
                }
                //play ufo sound
                if ( (int)u_sound.getStatus() != (int)sf::Sound::Status::Playing ||
                      u_sound.getPlayingOffset() >= sf::seconds(1.5 ) ) {
                    u_sound.setPlayingOffset( sf::seconds( 0.2f ) );
                    u_sound.play();
                }
                break;

            case Status::Destroyed :
                u_status = Status::Waiting; //put in waiting state
                break;
        }

    }

    void UFO::draw(sf::RenderTarget &window) {
        if ( u_status == Status::Flying ) {
            //draw ufo by frame
            u_sprite.setTextureRect( u_animation.getFrame() );
            window.draw( u_sprite );
        }
    }

    const sf::Vector2f& UFO::getPosition() const {
        return u_sprite.getPosition();
    }

    void UFO::onCollide(Collidable &other) {
        u_status = Status::Destroyed; // change status to destroyed
        u_sprite.setPosition( -1000, 0 ); //move away from screen so it cant collide with another object
    }

}
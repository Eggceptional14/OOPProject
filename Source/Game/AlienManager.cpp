#include "AlienManager.hpp"
#include "../Utility/Resources/ResHolder.hpp"
#include "Map.hpp"

#include <iostream>

namespace SI {

    const int MAX_ALIENS = 55;

    AlienManager::AlienManager(SI::Map &map)
    : a_moveGap( sf::seconds( 0.5f ) ), a_map( map )
    , a_alienRenderer( 12, 8, Alien::WIDTH, Alien::HEIGHT,
            ResourceHolder::get().textures.get( "aliens" ) ){

        //Aliens layout
        Alien::Type types[] = {
                Alien::Type::Squid, Alien::Type::Crab, Alien::Type::Crab,
                Alien::Type::Octopus, Alien::Type::Octopus
        };

        //Add each alien into vector a_aliens
        const int GAP = 10; //gap between each alien
        for ( int y = 0; y < 5; y ++ ) { //5 rows
            for ( int x = 0; x < 11; x++ ) { // 11 aliens in each row
                //calculate x, y position for each aliens
                float alienX = x * Alien::WIDTH + ( GAP * x * 3 ) + Alien::WIDTH;
                float alienY = y * Alien::HEIGHT + ( GAP * y ) + Alien::HEIGHT * 4;
                a_aliens.emplace_back( sf::Vector2f { alienX, alienY }, types[y] );
            }
        }

        //load alien sound
        for ( int i = 0; i < 4; i++ ) {
            a_moveSounds[i].setBuffer( ResourceHolder::get().sound_buffers.get(
                    "fastinvader" + to_string(i + 1 ) ) );
        }
        a_alienDeadSound.setBuffer( ResourceHolder::get().sound_buffers.get( "invaderkilled" ) );
    }

    void AlienManager::tryMoveAliens() {
        //move alien if clock is over timer
        if ( a_moveTimer.getElapsedTime() > a_moveGap ) {
            a_alienRenderer.nextFrame();

            //Calculate amount of move step
            bool moveDown = false;
            float step = a_moveLeft ? -10.0f : 10.0f;
            if ( a_movedown )
                step *= -1;
            a_moveSounds[ a_tick++ % 4 ].play(); //mod 4 so that it won't goes pass container bound

            //move alien
            for ( auto& alien : a_aliens ) {
                if ( !alien.isAlive() )
                    continue;
                alien.move( step, 0.0f );

                if ( a_movedown )
                    alien.move( 0, Alien::HEIGHT / 2.0 );
                else if ( !moveDown )
                    moveDown = checkAlienPos( alien ); //Check alien position if all should move down
            }

            if ( a_movedown )
                a_moveLeft = !a_moveLeft; //change side of movement from left to right or right to left
            a_movedown = moveDown;
            a_moveTimer.restart(); //restart move timer
        }
    }

    void AlienManager::drawAliens(sf::RenderTarget &target) {
        //draw all aliens in vector
        for (auto &alien : a_aliens) {
            if (!alien.isAlive())
                continue;
            a_alienRenderer.renderEntity(target, (int) alien.getType(), alien.getPosition());
        }
    }

    CollisionResult AlienManager::tryCollideWithProjectile(vector<Projectile> &projectiles) {
        CollisionResult result;
        vector<sf::Vector2f> collisionPoints;

        for ( auto& proj : projectiles ) {
            for ( auto& alien : a_aliens ) {
                if ( !alien.isAlive() || !proj.isActive() ) //projectile is not active or alien is dead
                    continue;
                if ( proj.tryCollide( alien ) ) { //if it collide with projectile
                    a_aliveAliens--;
                    a_alienDeadSound.play();
                    if ( a_aliveAliens == 0 ) //All aliens are dead
                        a_isAllAliensAdd = false;
                    result.second.emplace_back( alien.getPosition() );
                    result.first += ( (int)alien.getType() + 1 ) * 100; //add score based on alien type
                    updateMoveDelay();
                }
            }
        }
        return result;
    }

    sf::Vector2f AlienManager::getRandomLowestAlienPoint(Random<> &random) {
        if ( a_aliveAliens == 0 ) //all aliens are dead
            return { -1, -1 };
        //Loop until lowest alien is found
        while ( true ) {
            //get random column
            auto alienCol = random.getIntinRange( 0, 10 );
            for ( int y = 4; y >= 0; y-- ) {
                int index = y * 11 + alienCol;
                auto& alien = a_aliens.at( index ); //get alien at index
                if ( alien.isAlive() ) { //if that alien at the index is alive
                    return {
                        alien.getPosition().x + Alien::WIDTH / 2,
                        alien.getPosition().y + Alien::HEIGHT + 5
                    };
                }
            }
        }
    }

    int AlienManager::getAliveInvadersCount() const {
        return a_aliveAliens;
    }

    void AlienManager::initAddAlien() {
        static sf::Clock delay;
        if ( delay.getElapsedTime().asSeconds() > 0.02 ) {
            a_aliens.at( a_initY * 11 + a_initX ).makeAlive(); //add from bottom row first
            a_aliveAliens++; //add alive counter
            a_initX++; //increase column number
            if ( a_initX == 11 ) { //column limit
                a_initX = 0; //reset column number
                a_initY--; //reduce row
            }
            delay.restart();
        }

        if ( a_aliveAliens == MAX_ALIENS ) { //check for all aliens added or not
            a_isAllAliensAdd = true;
            a_initX = 0;
            a_initY = 4;
            updateMoveDelay();
        }

    }

    bool AlienManager::areAliensAlive() const {
        return a_isAllAliensAdd;
    }

    void AlienManager::updateMoveDelay() {
        a_moveGap = sf::seconds( (float)a_aliveAliens / 90.0f );
    }

    bool AlienManager::checkAlienPos(const SI::Alien &alien) const {

        if ( alien.getPosition().y > Display::HEIGHT - 150 ) //if aliens reach specific area game is over
            a_map.setGameOver();

        return (alien.getPosition().x < 15 && a_moveLeft) || //Check alien left side
               (alien.getPosition().x + Alien::WIDTH > Display::WIDTH - 15 && !a_moveLeft); //check alien right
    }

    void AlienManager::clearAlien() {
        a_aliens.clear();
    }
}
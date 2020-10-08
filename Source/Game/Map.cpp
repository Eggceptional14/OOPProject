#include "Map.hpp"
#include "../Utility/Resources/ResHolder.hpp"

namespace SI {

    Map::Map()
    : m_projectileRenderer( 4, 8, Projectile::WIDTH, Projectile::HEIGHT,
            ResourceHolder::get().textures.get("projectile" ) ),
             m_ufo( m_rng ),
             m_aliens( *this ) {

        //initialize explosion effect
        m_exploding.setSize( {52, 28 } );
        m_exploding.setTexture( &ResourceHolder::get().textures.get( "explosion" ) );

        //initialize Barrier
        const int SECT_SIZE = ( Display::WIDTH / 4 );
        for ( int i = 0; i < 4; i++ ) {
            m_barriers.emplace_back( float( i * SECT_SIZE + SECT_SIZE / 2 - Barrier::SIZE / 2 ) );
        }

        //initialize sound of player
        m_playerShot.setBuffer( ResourceHolder::get().sound_buffers.get("shoot" ) );
        m_playerShot.setVolume( 20 );
    }

    void Map::input() {
        if ( m_player.isAlive() ) { //if player is alive, input can then be taken
            if ( m_aliens.areAliensAlive() ) {
                m_player.input();
                playerShooting();
            }
        }
        else //player died then try to revive the player
            m_player.revive();
    }

    int Map::update(float dt) {
        int score = 0;

        if( m_isGameOver )
            m_aliens.clearAlien();

        if ( m_aliens.areAliensAlive() ) { // all aliens are alive
            m_player.update(dt);
            if (m_player.isAlive()) { // player is alive
                //move aliens toward player and control aliens shooting
                m_aliens.tryMoveAliens();
                enemyShooting();

                //pair score you get with point of collision list
                auto collisionResult = getCollisionResult(dt);
                if ( collisionResult.second.size() > 0 ) {
                    score += collisionResult.first;
                    for (auto &point : collisionResult.second)
                        m_explosions.emplace_back(point);
                }
                m_ufo.update(dt); //update ufo frame
            }

            //control explosion life time
            for ( auto it = m_explosions.begin(); it != m_explosions.end(); ) {
                if ( it->isOver() )
                    it = m_explosions.erase( it );
                else
                    it++;
            }
        }
        else { //if aliens are all dead
            //create new aliens at the starting point
            m_aliens.initAddAlien();
            m_projectiles.clear();
            m_explosions.clear();
        }
        return score; //give score update
    }

    //draw every entities on to the screen
    void Map::draw(sf::RenderTarget &target) {
        //projectile animation
        if( m_animationTimer.getElapsedTime().asSeconds() > 0.2 ) {
            m_projectileRenderer.nextFrame();
            m_animationTimer.restart();
        }

        //draw barrier
        for ( auto& barrier : m_barriers )
            barrier.draw( target );

        //draw projectile
        for ( auto& proj : m_projectiles ) {
            m_projectileRenderer.renderEntity( target, (int)proj.getType(), proj.getPosition() );
        }

        //draw explosion animation
        for ( auto& exps : m_explosions ) {
            m_exploding.setPosition( exps.getPosition() );
            target.draw( m_exploding );
        }

        m_aliens.drawAliens( target );
        m_player.draw( target );
        m_ufo.draw( target );
    }

    const Player& Map::getPlayer() const {
        return m_player;
    }

    bool Map::isGameOver() const {
        return m_player.getLives() == -1 || m_isGameOver;
    }

    void Map::setGameOver() {
        m_isGameOver = true;
    }

    void Map::playerShooting() {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && //Space key used to shoot
        m_playerShotClock.getElapsedTime().asSeconds() > 0.5f ) //shotClock use to prevent user from firing too fast
        {
            auto point = m_player.gunPos(); //get gun position
            point.x -= Projectile::WIDTH / 2.0f;
            point.y -= Projectile::HEIGHT;

            //add projectile to projectile vector for draw and update funciton to use the object
            m_projectiles.emplace_back( point, Projectile::Type::Bullet, Projectile::Direction::Up );
            m_playerShotClock.restart();
            m_playerShot.play(); //play shooting sound
        }
    }

    void Map::enemyShooting() {
        //shot clock is used to control how fast aliens can shoot
        if ( m_alienShotClock.getElapsedTime().asSeconds() >= 0.1 && m_rng.getIntinRange( 0, 30 ) == 2 ) {
            auto point = m_aliens.getRandomLowestAlienPoint( m_rng ); //Randomly choose lowest alien
            if ( (int)point.x == -1 )
                return;

            //random type of projectile
            auto type = static_cast<Projectile::Type> ( m_rng.getIntinRange(1,2 ) );
            //add projectile to vector
            m_projectiles.emplace_back( point, type, Projectile::Direction::Down );
            m_alienShotClock.restart();
        }
    }

    CollisionResult Map::getCollisionResult(float dt) {
        //get score from hitting aliens ( score differ by types of alien )
        auto result = m_aliens.tryCollideWithProjectile( m_projectiles );
        updateProjectiles( dt, result.second );

        for( auto& proj : m_projectiles ) {

            //Projectile on contact with barrier
            for ( auto& barrier : m_barriers ) {
                if ( barrier.isHit( proj ) ) {
                    proj.destroy(); //destroy part of barrier
                    result.second.emplace_back( proj.getPosition() );
                }
            }

            //Projectile on contact with ufo
            if ( m_ufo.tryCollide( proj ) ) {
                result.second.emplace_back( proj.getPosition() );
                result.first += 200;
            }

            //Projectile on contact with another projectile
            for ( auto& otherProj : m_projectiles ) {
                if ( otherProj.getOwner() != proj.getOwner() ) {
                    if ( otherProj.tryCollide( proj ) )
                        result.second.emplace_back( proj.getPosition() );
                }
            }
        }
        return result;
    }

    void Map::updateProjectiles(float dt, vector<sf::Vector2f> &collisionPoints) {
        //loop for all projectile in vector
        for ( auto it = m_projectiles.begin(); it != m_projectiles.end(); ) {
            auto& projectile = *it;
            if ( !projectile.isActive() )
                it = m_projectiles.erase(it );
            else {
                //check for projectile collide with player
                if ( projectile.tryCollide( m_player ) ) {
                    collisionPoints.emplace_back( ( m_player.gunPos() ) );
                    m_projectiles.clear();
                    return;
                }
                projectile.update( dt );
                it++;
            }
        }
    }

}
#ifndef SPACE_INVADER_MAP_HPP
#define SPACE_INVADER_MAP_HPP

#include <SFML/Graphics.hpp>

#include "Renderer/LRenderer.hpp"
#include "AlienManager.hpp"
#include "Entity/UFO.hpp"
#include "Entity/Player.hpp"
#include "Entity/Projectile.hpp"
#include "Entity/Explosion.hpp"
#include "Entity/Barrier.hpp"

namespace SI {
    class Map {
    public:
        Map();

        void input(); //handle input from user
        int update( float dt ); //update frame
        void draw( sf::RenderTarget& target ); //render frame

        const Player& getPlayer() const; //return player entity

        bool isGameOver() const; //return true if game is over

        void setGameOver(); //set game over

    private:
        void playerShooting(); //control player shooting
        void enemyShooting(); //control alien shooting

        CollisionResult getCollisionResult(float dt ); //return collision result of object

        void updateProjectiles( float dt, vector<sf::Vector2f>& collisionPoints ); //update projectile frame

        bool m_isGameOver = false;

        LRenderer m_projectileRenderer;
        AlienManager m_aliens;
        Player m_player;
        UFO m_ufo;

        //vector store entities that can have large number of them occur on the map
        vector<Projectile> m_projectiles;
        vector<Explosion> m_explosions;
        vector<Barrier> m_barriers;

        sf::RectangleShape m_exploding; //explode sprite

        sf::Sound m_playerShot;

        sf::Clock m_alienShotClock;
        sf::Clock m_playerShotClock;
        sf::Clock m_animationTimer;

        Random<> m_rng;
    };
}
#endif

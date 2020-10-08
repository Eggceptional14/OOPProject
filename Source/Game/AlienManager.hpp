#ifndef SPACE_INVADER_ALIENMANAGER_HPP
#define SPACE_INVADER_ALIENMANAGER_HPP

#include "Entity/Projectile.hpp"
#include "Entity/Alien.hpp"
#include "Renderer/LRenderer.hpp"
#include "DispInform.hpp"
#include "../Utility/Extra/Random.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

namespace SI {

    class Map;

    //pair score with vector of vector2f position
    using CollisionResult = pair<int, vector<sf::Vector2f>>;

    /*
     * This class is used to manage alien's rendering and updating
     */

    class AlienManager {
    public:
        AlienManager( Map& map );

        //Move all aliens to left or right side of the screen
        void tryMoveAliens();

        //draw all alien on the map
        void drawAliens( sf::RenderTarget& target );

        /*
         * try collide with another projectile and return Collision result
         */
        CollisionResult tryCollideWithProjectile(vector<Projectile>& projectiles );

        //get lowest aliens on the column
        sf::Vector2f getRandomLowestAlienPoint( Random<>& random );

        //get number of aliens that are alive
        int getAliveInvadersCount() const;

        //add alien one at a time until all aliens have been added
        void initAddAlien();

        //tell if aliens are all alive
        bool areAliensAlive() const;

        void clearAlien();

    private:
        //change time delay before aliens start moving based on number of alive aliens
        void updateMoveDelay();

        //check position of the alien to see if all aliens should move down or if the game is over
        bool checkAlienPos( const Alien& alien ) const;

        vector<Alien> a_aliens;
        sf::Clock a_moveTimer;
        sf::Time a_moveGap;

        Map& a_map;

        sf::Sound a_moveSounds[4];
        sf::Sound a_alienDeadSound;

        LRenderer a_alienRenderer;

        unsigned a_aliveAliens;

        bool a_isAllAliensAdd = false;

        bool a_moveLeft = false;
        bool a_movedown = false;

        int a_initX = 0; //Column number
        int a_initY = 4; //Row number
        int a_tick = 0;
    };
}

#endif

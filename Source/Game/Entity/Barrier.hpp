#ifndef SPACE_INVADER_BARRIER_HPP
#define SPACE_INVADER_BARRIER_HPP

#include <SFML/Graphics.hpp>
#include <array>

#include "../Collidable.hpp"

using namespace std;

namespace SI {

    class Projectile;

    /*
     * Barrier separate into 16 section
     */

    class Barrier : public Collidable {

        const static int SECT_SIZE = 20;

        enum class SectorStyle {
            Square,
            SlopeUp,
            SlopeDown,
            UnderSlopeUp,
            UnderSlopeDown,
        };

        class Section : public Collidable {
        public:
            Section( float tlX, float tlY, SectorStyle style );

            void draw( sf::RenderTarget& target ); //draw barrier section

            const sf::Vector2f& getPosition() const override; //return vector2f position
            void onCollide( Collidable& other ) override{} //action when projectile collide with barrier

            sf::Vector2f isHit( const Projectile& other ); //return hit postion

            void destroyPoint(int x, int y ); //destroy section pixel

        private:
            //calculate pixel coordinate of single section
            void calculatePixelCoord( int x, int y, sf::Vertex& v, SectorStyle style );

            array<sf::Vertex, SECT_SIZE * SECT_SIZE> s_pixels;
            sf::Vector2f s_position;
        };

    public:
        const static int SIZE = SECT_SIZE * 4;

        Barrier( float x );

        void draw( sf::RenderTarget& target ); //draw whole barrier
        bool isHit( const Projectile& projectile ); //return true if barrier collide with projectile

        const sf::Vector2f& getPosition() const override; //return barrier position
        void onCollide( Collidable& other ) override {} //action when barrier collide with another object

    private:
        Section& getSection( int x, int y ); //get section of the barrier

        void destroyPart( float relX, float relY ); //destroy part of barrier

        vector<Section> b_sections;
        sf::Vector2f b_position;
    };
}

#endif

#include "Barrier.hpp"
#include "../DispInform.hpp"
#include "Projectile.hpp"
#include "../../Utility/Extra/Random.hpp"

#include <iostream>

namespace SI {

    Barrier::Barrier( float x )
    :Collidable( (float)SIZE, (float)SIZE ), b_position( x, Display::HEIGHT - 200 ) {

        using Sty = SectorStyle;
        for ( float sy = 0; sy < 4; sy++ ) {
            for ( float sx = 0; sx < 4; sx++ ) {
                Sty style = Sty::Square;
                int xP = (int)sx;
                int yP = (int)sy;
                //Change style of section base on index
                if ( xP == 0 && yP == 0 ) //top left
                    style = Sty::SlopeUp;
                if ( xP == 3 && yP == 0 ) //top right
                    style = Sty::SlopeDown;
                if ( xP == 1 && yP == 3 ) //bottom left
                    style = Sty::UnderSlopeUp;
                if ( xP == 2 && yP == 3 ) //bottom right
                    style = Sty::UnderSlopeDown;
                //add to section vector
                b_sections.emplace_back( x + sx * SECT_SIZE, b_position.y + sy * SECT_SIZE, style );
            }
        }
    }

    void Barrier::draw(sf::RenderTarget &target) {
        //draw all sections
        for ( auto& sect : b_sections ) {
            sect.draw( target );
        }
    }

    bool Barrier::isHit(const Projectile &projectile) {

        static Random<> rand;

        if ( projectile.getBox().intersects( getBox() ) ) { //projectile collide with barrier part
            for ( auto& sector : b_sections ) {
                auto result = sector.isHit( projectile );

                if ( (int)result.x == -1 ) //not collide
                    continue;
                else { // projectile collide with barrier

                    //Get coordinate of collision point relate to top left of barrier
                    result.x -= b_position.x;
                    result.y -= b_position.y;

                    //Destroy pixel around point of collision
                    for ( int y = -3; y < 3; y++ ) {
                        for ( int x = -3; x < 3; x++ ) {
                            float newRelX = result.x + x * 2;
                            float newRelY = result.y + y * 2;
                            destroyPart( newRelX, newRelY );
                        }
                    }

                    //blast damage
                    float radius = 12.0;
                    for ( int i = 0; i < 35; i++ ) {
                        //random pixel
                        float newRelX = result.x + rand.getFloatinRange( -radius, radius );
                        float newRelY = result.y + rand.getFloatinRange( -radius, radius );
                        destroyPart( newRelX, newRelY );
                    }
                    return true;
                }
            }
        }
        return false;
    }

    const sf::Vector2f& Barrier::getPosition() const {
        return b_position;
    }

    Barrier::Section& Barrier::getSection(int x, int y) {
        return b_sections[ y * 4 + x ];
    }

    void Barrier::destroyPart(float relX, float relY) {
        //check for out of bound
        if ( relX < 0 || relX >= SIZE || relY < 0 || relY >= SIZE )
            return;

        //get section of barrier
        int xIndex = (int)relX / SECT_SIZE;
        int yIndex = (int)relY / SECT_SIZE;
        auto& section = getSection( xIndex, yIndex );
        auto& sectionPos = section.getPosition();

        //Find pixel coordinate
        float sectionTopLeftX = sectionPos.x - b_position.x;
        float sectionTopLeftY = sectionPos.y - b_position.y;
        float pixelX = relX - sectionTopLeftX;
        float pixelY = relY - sectionTopLeftY;

        //destroy point in the section
        section.destroyPoint((int) pixelX, (int) pixelY);
    }

    //Section class

    //tlX, tlY ( top left x, y ) use to tell another position
    Barrier::Section::Section(float tlX, float tlY, SI::Barrier::SectorStyle style)
    : Collidable( (float)SECT_SIZE, (float)SECT_SIZE ), s_position( { tlX, tlY } )
    {
        for ( float y = 0; y < SECT_SIZE; y++ ) {
            for ( float x = 0; x < SECT_SIZE; x++ ) {
             sf::Vertex pixel;
             pixel.color = sf::Color::White;
             pixel.position = { x + tlX, y + tlY };
             calculatePixelCoord( (int)x, (int)y, pixel, style );
            }
        }
    }

    void Barrier::Section::draw(sf::RenderTarget &target) {
        target.draw( s_pixels.data(), s_pixels.size(), sf::Points );
    }

    const sf::Vector2f& Barrier::Section::getPosition() const {
        return s_position;
    }

    sf::Vector2f Barrier::Section::isHit(const Projectile &other) {
        for ( auto& px : s_pixels ) {
            //Check for collision by both x, y position and color of the pixel
            if ( other.getBox().contains( px.position ) && px.color == sf::Color::White ) {
                return px.position;
            }
        }
        return { -1, 1 };
    }

    void Barrier::Section::destroyPoint(int x, int y) {
        for ( int oY = -2; oY <= 2; oY++ ) {
            for ( int oX = -2; oX <= 2; oX++ ) {
                int newX = x + oX;
                int newY = y + oY;

                if ( newX < 0 || newX >= SECT_SIZE || newY < 0 || newY >= SECT_SIZE )
                    continue;
                //destroy point by black out the pixel
                s_pixels[ newY * SECT_SIZE + newX ].color = sf::Color::Black;
            }
        }
    }

    void Barrier::Section::calculatePixelCoord(int x, int y, sf::Vertex &v, SI::Barrier::SectorStyle style) {
        //each section contains different pixel coordinate
        switch ( style ) {
            case SectorStyle::Square:
                s_pixels[y * SECT_SIZE + x] = v;
                break;

            case SectorStyle::SlopeUp:
                if ( SECT_SIZE - y < x )
                    s_pixels[y * SECT_SIZE + x] = v;
                break;

            case SectorStyle::SlopeDown:
                if ( x < y )
                    s_pixels[y * SECT_SIZE + x] = v;
                break;

            case SectorStyle::UnderSlopeUp:
                if ( SECT_SIZE - x > y )
                    s_pixels[y * SECT_SIZE + x] = v;
                break;

            case SectorStyle::UnderSlopeDown:
                if ( x > y )
                    s_pixels[y * SECT_SIZE + x] = v;
                break;
        }
    }
}

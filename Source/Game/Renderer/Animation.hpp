#ifndef SPACE_INVADER_ANIMATION_HPP
#define SPACE_INVADER_ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

namespace SI {

    class Animation {
    public:
        struct Frame { //single frame
            Frame( const sf::IntRect& bds, sf::Time dly ) //bds = bounds
            : bounds( bds ), delay( dly ) {}

            sf::IntRect bounds; //The area of the texture in one frame
            sf::Time delay; //Time delay before rendering next frame
        };

        Animation( unsigned framwWidth, unsigned frameHeight );

        void addFrame( unsigned index, sf::Time dly ); //add new frame

        const sf::IntRect& getFrame(); //get single frame

    private:

        unsigned frame_index = 0;
        const unsigned FRAME_WIDTH;
        const unsigned FRAME_HEIGHT;

        sf::Clock timer;
        vector<Frame> frame;

    };
}

#endif

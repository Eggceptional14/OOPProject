#include "Animation.hpp"

namespace SI {

    Animation::Animation(unsigned frameWidth, unsigned frameHeight)
    : FRAME_WIDTH( frameWidth ), FRAME_HEIGHT( frameHeight )
    {}

    void Animation::addFrame(unsigned int index, sf::Time dly) {
        sf::IntRect bounds;

        //frame boundary
        bounds.top = 0;
        bounds.width = FRAME_WIDTH;
        bounds.height = FRAME_HEIGHT;
        bounds.left = index * FRAME_WIDTH;

        //add frame to vector
        frame.emplace_back( bounds, dly );
    }

    const sf::IntRect& Animation::getFrame() {
        if ( timer.getElapsedTime() >= frame[frame_index].delay ) {
            timer.restart();
            frame_index += 1; //next frame index

            if( frame_index == frame.size() )
                frame_index = 0; //reach end of frame
        }
        return frame[frame_index].bounds;
    }
}
#ifndef SPACE_INVADER_LRENDERER_HPP
#define SPACE_INVADER_LRENDERER_HPP

#include <SFML/Graphics.hpp>

namespace SI {

    /*
     * Utility class for handling a task of rendering a large number of entities, which
     * has the same animation such as the aliens ( enemy )
     */

    class LRenderer {
    public:
        LRenderer( int frameWdth, int frameHeight, float entityWidth, float entityHeight,
                   const sf::Texture& sprite );

        void nextFrame(); //change frame

        void renderEntity( sf::RenderTarget& renderer, int type, const sf::Vector2f& pos ); //render all entities

    private:
        int currentFrame;
        const int frame_width;
        const int frame_height;
        sf::RectangleShape entity;

    };
}

#endif

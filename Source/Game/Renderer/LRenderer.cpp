#include "LRenderer.hpp"

namespace SI {

    LRenderer::LRenderer(int frameWidth, int frameHeight, float entityWidth, float entityHeight,
            const sf::Texture &sprite)
            : frame_width( frameWidth )
            , frame_height( frameHeight ){

        //set entity property
        entity.setSize( { entityWidth, entityHeight } );
        entity.setTexture( &sprite );
    }

    void LRenderer::nextFrame() {
        currentFrame += 1;
    }

    void LRenderer::renderEntity(sf::RenderTarget &renderer, int type, const sf::Vector2f &pos) {

        int textureLeft = (currentFrame % 2) * frame_width; //frame left side
        int textureTop = type * frame_height; //frame top side

        entity.setPosition( pos );
        entity.setTextureRect( { textureLeft, textureTop, frame_width, frame_height } );
        renderer.draw( entity );
    }

}
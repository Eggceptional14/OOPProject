#include "ResHolder.hpp"

ResourceHolder& ResourceHolder::get() {
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
: fonts( "Font", "TTF" )
, textures( "Texture", "png" )
, sound_buffers("SFX", "wav" ){
}

#ifndef SPACE_INVADER_MAINMENU_HPP
#define SPACE_INVADER_MAINMENU_HPP

#include "../../Utility/GameState/GameState.hpp"
#include "../../Utility/GUI/Button.hpp"

namespace SI {

    class StateMainMenu : public GameState {
    public:
        StateMainMenu( MGame& game );

        void eventHandler( sf::Event e ) override; //handle window event
        void render( sf::RenderTarget& renderer ) override;

    private:
        sf::RectangleShape m_banner;
        unique_ptr<gui::Button> playBtn;
    };


}

#endif

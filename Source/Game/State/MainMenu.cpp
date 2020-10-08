#include "MainMenu.hpp"
#include "../DispInform.hpp"
#include "Playing.hpp"
#include "../../Main/MGame.hpp"

namespace SI {

    StateMainMenu::StateMainMenu(MGame &game)
    :GameState( game, "Main Menu", Display::WIDTH, Display::HEIGHT ) {

        //Initialize banner properties
        m_banner.setSize( { (float)Display::WIDTH - 100, 200 } );
        m_banner.setTexture( &ResourceHolder::get().textures.get( "logo" ) );
        m_banner.setPosition( Display::WIDTH / 2.0f - m_banner.getSize().x / 2.0f, 100 );

        //////////////////////////////////

        //initialize and create button widget
        playBtn = gui::makeButton();
        playBtn->setText("Play" );
        playBtn->setFunction([&]() {
            pGame->pushState<StatePlaying>( *pGame );
        });
        playBtn->setPosition( { static_cast<float>( Display::WIDTH / 2.0 - playBtn->getSize().x / 2.0 )
                                , Display::HEIGHT - 200 } );

        //////////////////////////////////
    }

    void StateMainMenu::eventHandler(sf::Event e) {
        //send event to button class
        playBtn->handleEvent( e, pGame->getWindow() );
    }

    void StateMainMenu::render(sf::RenderTarget &renderer) {
        //draw everything in main menu window
        renderer.draw( m_banner );
        playBtn->render( renderer );
    }

}
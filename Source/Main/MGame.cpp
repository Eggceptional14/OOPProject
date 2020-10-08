#include "MGame.hpp"
#include "../Game/DispInform.hpp"

#include <iostream>

MGame::MGame()
:g_window( { 1280, 720 }, "Space Invaders" ) {

    g_window.setPosition( {g_window.getPosition().x, 0 } );
    g_window.setFramerateLimit( 60 );

}

void MGame::run() {
    const unsigned TPS = 30;
    const sf::Time timePerUpdate = sf::seconds(( 1.0 / (float)TPS ) );

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;

    //Main game loop
    while ( g_window.isOpen() && !g_states.empty() ) {
        auto& state = getCurrentState();

        //get time
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time; // lastTime = last frame time

        //time update
        state.inputHandler();
        state.update( elapsed );

        //render entity
        g_window.clear();
        state.render( g_window );
        g_window.display();

        //handle window's event
        handleEvent();
        //control changing of game state
        tryPop();
    }
}

void MGame::resizeWindow(unsigned int width, unsigned int height) {
    g_window.close();
    g_window.create( { width, height }, "Space Invaders" );
}

const sf::RenderWindow& MGame::getWindow() const {
    return g_window;
}

void MGame::pushState( unique_ptr<GameState> state ) {
    g_states.push_back( move( state ) ); // move game state from unique pointer to state vector
    getCurrentState().onOpen();
}

void MGame::handleEvent() {
    sf::Event e; //handle window event
    while ( g_window.pollEvent(e ) ) {
        getCurrentState().eventHandler( e );
        switch ( e.type ) {
            case sf::Event::Closed:
                g_window.close();
                break;
            default:
                break;
        }
    }
}

void MGame::tryPop() {
    if ( g_shouldPop ) {
        g_shouldPop = false;
        if ( g_shouldExit ) {
            //clear vector when exit the game
            g_states.clear();
            return;
        }
        else if ( g_shouldChangeState ) {
            g_shouldChangeState = false;
            g_states.pop_back(); //pop old state out of vector
            pushState( move( g_change ) ); //push new state into vector
            return;
        }

        g_states.pop_back(); //pop state out of vector
        if ( !g_states.empty() ) {
            getCurrentState().onOpen();
        }
    }
}

GameState& MGame::getCurrentState() {
    return *g_states.back();
}
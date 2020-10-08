#ifndef SPACE_INVADER_GAMEOVER_HPP
#define SPACE_INVADER_GAMEOVER_HPP

#include "../../Utility/GameState/GameState.hpp"
#include "../../Utility/GUI/Button.hpp"
#include "../../Utility/Extra/Score.hpp"

namespace SI {

    class StateGameOver : public GameState {
    public:
        StateGameOver( MGame &game );

        void eventHandler( sf::Event e ) override; //handle window event
        void render( sf::RenderTarget& renderer ) override; //render object

    private:
        Score tScore; //use for getting score from file

        gui::Widget::Text scoreLabel; //Label for current score
        gui::Widget::Text highscoreLabel; //Label for highest score

        unique_ptr<gui::Button> playBtn; //Button to play the game again

        sf::RectangleShape ovBanner; //Game over picture
    };
}

#endif

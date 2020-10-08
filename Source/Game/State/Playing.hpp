#ifndef SPACE_INVADER_PLAYING_HPP
#define SPACE_INVADER_PLAYING_HPP

#include "../../Utility/GameState/GameState.hpp"
#include "../Map.hpp"
#include "../../Utility/GUI/Widget.hpp"
#include "../../Utility/Extra/Score.hpp"

using namespace std;

namespace SI {

    /*
     * This state class is the state of all gameplay are happening
     */
    class StatePlaying : public GameState {
    public:
        StatePlaying( MGame& game );

        void inputHandler( ) override; //handle input
        void update( sf::Time deltaTime ) override; //update frame
        void render( sf::RenderTarget& renderer ) override; //render entities

    private:
        Score mScore;

        Map p_map;

        int p_score = 0;
        bool p_gameOver = false;

        sf::Clock p_gameOverClock;

        //player health display
        class HealthDisplay {
        public:
            HealthDisplay();

            void draw( sf::RenderTarget& window, int lives ); //draw all widget

        private:
            gui::Widget::Text hLabel;
            sf::RectangleShape healthIcon;
        }health_display;

        //Display player's score
        class ScoreDisplay {
        public:
            ScoreDisplay( float centerX, const string& text );

            void update( int newScore ); //update score overtime

            void draw( sf::RenderTarget& target ); //render score label on the screen

            int getCurrentDisplayScore() const; //get score displaying on the screen

        private:
            void updateDisplay(); //update the score label on the screen

            gui::Widget::Text sLabel;
            string score_text;
            int v_currentScore;
            float centerPos;
        }currentScore, highScore;

    };
}
#endif

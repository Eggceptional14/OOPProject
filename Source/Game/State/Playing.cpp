#include "Playing.hpp"
#include "../../Main/MGame.hpp"
#include "GameOver.hpp"

#include <iostream>

namespace SI {

    StatePlaying::StatePlaying(MGame &game)
    : GameState( game, "Playing the game" )
    , currentScore( Display::WIDTH / 8, "Score" )
    , highScore( Display::WIDTH / 2, "HighScore" )
    , mScore( "score", "txt" ) {

        //set high score
        highScore.update( mScore.getHighScore() );
    }

    void StatePlaying::inputHandler() {
        p_map.input();
    }

    void StatePlaying::update(sf::Time deltaTime) {
        if ( !p_gameOver ) { //update frame if game is not over
            p_score += p_map.update( deltaTime.asSeconds() );
            currentScore.update( p_score );

            if ( p_score > highScore.getCurrentDisplayScore() ) { //change highscore if current score exceed the highscore
                highScore.update( p_score );
            }
        }

        p_gameOver = p_map.isGameOver();
    }

    void StatePlaying::render(sf::RenderTarget &renderer) {
        //draw everything
        p_map.draw( renderer );
        health_display.draw( renderer, p_map.getPlayer().getLives() );
        currentScore.draw( renderer );
        highScore.draw( renderer );

        if ( p_gameOver ) { //change state of the game when game is over
            mScore.addScore( currentScore.getCurrentDisplayScore() );
            pGame->changeState<StateGameOver>(*pGame);
        }
    }

    //---Health Display---

    StatePlaying::HealthDisplay::HealthDisplay() {

        //Set properties of health stamp
        healthIcon.setSize( { Player::WIDTH / 2, Player::WIDTH / 2 } );
        healthIcon.setTexture( &ResourceHolder::get().textures.get( "player" ) );
        healthIcon.setTextureRect( { 0, 0, 11, 8 } );

        //Set properties of health label
        hLabel.setPosition( Display::WIDTH - ( Player::WIDTH * 5 ), 10 );
        hLabel.setString( "Health" );
        hLabel.setOutlineThickness( 0 );
    }

    void StatePlaying::HealthDisplay::draw(sf::RenderTarget &window, int lives) {
        //set x and y starting pos
        float xOrigin = hLabel.getPosition().x + hLabel.getGlobalBounds().width + 10;
        float yOrigin = hLabel.getPosition().y + hLabel.getGlobalBounds().height / 2;

        window.draw( hLabel );

        for( int i = 0; i < lives; i++ ) {
            //draw player icon which represent player's health one by one
            healthIcon.setPosition( xOrigin + i * Player::WIDTH / 2 + i * 10, yOrigin );
            window.draw( healthIcon );
        }
    }

    //Score display
    StatePlaying::ScoreDisplay::ScoreDisplay(float centerX, const string &text)
    : score_text( text ), centerPos( centerX ) {
        updateDisplay(); //update score display
        sLabel.setOutlineThickness( 0 );
    }

    void StatePlaying::ScoreDisplay::update(int newScore) {
        v_currentScore = newScore; //update new score
        updateDisplay(); //update score display
    }

    void StatePlaying::ScoreDisplay::draw(sf::RenderTarget &target) {
        target.draw( sLabel );
    }

    int StatePlaying::ScoreDisplay::getCurrentDisplayScore() const {
        return v_currentScore;
    }

    void StatePlaying::ScoreDisplay::updateDisplay() {
        sLabel.setString( score_text + "   " + to_string( v_currentScore ) ); //set new score
        sLabel.setPosition( centerPos - sLabel.getGlobalBounds().width / 2, 15 );
    }
}
#include "GameOver.hpp"
#include "../DispInform.hpp"
#include "Playing.hpp"
#include "../../Main/MGame.hpp"

namespace SI {

    StateGameOver::StateGameOver(MGame &game)
            : GameState(game, "Main Menu", Display::WIDTH, Display::HEIGHT)
            , tScore( "score", "txt" ) {
        //initialize Banner
        ovBanner.setSize({(float) Display::WIDTH - 100, 200});
        ovBanner.setTexture(&ResourceHolder::get().textures.get("gameover"));
        ovBanner.setPosition(Display::WIDTH / 2.0f - ovBanner.getSize().x / 2.0f, 100);

        //////////////////////////////////

        //create and initialize button widget
        playBtn = gui::makeButton();
        playBtn->setText("Play Again");
        playBtn->setFunction([&]() {
            pGame->changeState<StatePlaying>(*pGame);
        });
        playBtn->setPosition(
                {static_cast<float>( Display::WIDTH / 2.0f - playBtn->getSize().x / 2.0f ), Display::HEIGHT - 200});

        //////////////////////////////////

        //Set all properties of score label
        scoreLabel.setString( "Score  " + to_string(tScore.getCurrentScore() ) );
        scoreLabel.setFont( ResourceHolder::get().fonts.get( "arcade") );
        scoreLabel.setCharacterSize( 35 );
        scoreLabel.setPosition( Display::WIDTH / 2 - scoreLabel.getGlobalBounds().width / 2, Display::HEIGHT / 2 );

        //////////////////////////////////

        //set properties of high score label
        highscoreLabel.setString( "High Score  " + to_string(tScore.getHighScore() ) );
        highscoreLabel.setFont( ResourceHolder::get().fonts.get( "arcade") );
        highscoreLabel.setCharacterSize( 35 );
        highscoreLabel.setPosition( Display::WIDTH / 2 - highscoreLabel.getGlobalBounds().width / 2, Display::HEIGHT / 2 + 60 );

        //////////////////////////////////

    }

    void StateGameOver::eventHandler(sf::Event e) {
        //send event to button class to handle
        playBtn->handleEvent(e, pGame->getWindow());
    }

    void StateGameOver::render(sf::RenderTarget &renderer) {
        //draw everything needed for game over page
        renderer.draw(ovBanner);
        renderer.draw( scoreLabel );
        renderer.draw( highscoreLabel );
        playBtn->render(renderer);
    }
}
#ifndef SPACE_INVADER_GAMESTATE_HPP
#define SPACE_INVADER_GAMESTATE_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class MGame;

/*
 * Base-class for game state
 */

class GameState : public sf::NonCopyable {
public:
    GameState( MGame& game, const char* name );

    GameState( MGame& game, const char* name, unsigned resizeWinWidth, unsigned resizeWinHeight );

    virtual ~GameState() = default;

    virtual void onOpen() {} //on open of that state
    virtual void eventHandler( sf::Event e ) {} //handle event
    virtual void inputHandler() {} //handle all user input
    virtual void update( sf::Time c_time ) {} //update frame
    virtual void render( sf::RenderTarget& renderer ) = 0; //render entity and object

    const std::string& getName() const { return pName; } //return state name

protected:
    MGame* pGame;
    std::string pName;
};

#endif
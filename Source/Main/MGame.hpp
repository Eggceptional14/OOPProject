#ifndef SPACE_INVADER_MGAME_HPP
#define SPACE_INVADER_MGAME_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Utility/GameState/GameState.hpp"

using namespace std;

/*
 * Main class that control all functions of the game
 */

class MGame : public sf::NonCopyable {
public:
    MGame();

    void run(); //Main game loop

    void resizeWindow( unsigned width, unsigned height ); //resize the game window

    const sf::RenderWindow& getWindow() const;

    template <typename T>
    void initGame(); //initialize the game

    void pushState( unique_ptr<GameState> state ); //push game state into state vector

    template <typename T, typename... Args>
    void pushState( Args&&... args ); //call pushState function

    template <typename T, typename... Args>
    void changeState( Args&&... args ); //change game state

public:
    void handleEvent(); //handle all window event
    void tryPop(); //try to pop element from state vector

    GameState& getCurrentState(); //return current game state

    sf::RenderWindow g_window; //render window
    vector<unique_ptr<GameState>> g_states; //vector storing game state

    bool g_shouldPop = false;
    bool g_shouldExit = false;
    bool g_shouldChangeState = false;

    unique_ptr<GameState> g_change;
};

/*
 * Game state machine
 */

template <typename T>
inline void MGame::initGame() {
    //initialize game state
    this->pushState<T> ( *this );
}

template <typename T, typename... Args>
inline void MGame::pushState(Args &&... args) {
    //call pushState function
    pushState( make_unique<T>( forward<Args>( args )... ) );
}

template <typename T, typename... Args>
inline void MGame::changeState(Args &&... args) {
    //change the game state
    g_change = make_unique<T>( forward<Args>( args )... );
    g_shouldPop = true;
    g_shouldChangeState = true;
}

#endif

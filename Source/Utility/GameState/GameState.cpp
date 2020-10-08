#include "GameState.hpp"

#include "../../Main/MGame.hpp"

GameState::GameState(MGame &game, const char* name)
: pGame( &game ), pName( name ) {
}

GameState::GameState(MGame &game, const char* name, unsigned resizeWinWidth, unsigned resizeWinHeight)
: pGame( &game ), pName( name ){
    pGame->resizeWindow( resizeWinWidth, resizeWinHeight );
}


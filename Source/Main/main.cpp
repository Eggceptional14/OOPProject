#include "../Main/MGame.hpp"
#include "../Game/State/MainMenu.hpp"

using namespace std;

//function use to run game
template <typename T>
void run() {
    MGame app;
    app.initGame<T>(); //push first state in to state vector
    app.run();
}

int main() {

    run<SI::StateMainMenu>();

    return 0;
}

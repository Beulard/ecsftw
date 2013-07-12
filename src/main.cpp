#include "Game.hpp"

FILE* gamelog;
Game game;
float projMatrix[9];

int main(int argc, char** argv) {
    if( !game.Init() )
        return 1;
    game.Run();
    game.Exit();

    return 0;
}

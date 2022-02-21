#include "Game.h"
#include "stdafx.h"
#include "Player.h"

using namespace sf;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    Game game;

    while (game.getWindow().isOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}
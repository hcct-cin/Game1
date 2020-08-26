#include "Game.h"

int main() {

    Game game;


    while (game.running()) {
        
        // Update
        game.updateMenu();

        // Render
        game.renderMenu();

    }

    return 0;
}



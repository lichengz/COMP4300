#include "GameEngine.h"
#include "GameSettings.h"


int main() {

    GameSettings settings = GameSettings();
    settings.readConfigFile();
    settings.init_shapes();

    GameEngine gameEngine = GameEngine(settings);
    gameEngine.start();
    gameEngine.update();

    return 0;
}

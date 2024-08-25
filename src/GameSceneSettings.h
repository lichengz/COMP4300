//
// Created by white on 2024-08-24.
//

#ifndef GAMESCENESETTINGS_H
#define GAMESCENESETTINGS_H
#include <string>

#include "Vec2.h"

class GameSceneSettings {
public:
    // IDLE ANIMATION
    std::string idleAnimPath = "bin/images/mario_idle.png";
    size_t idleAnimFrameCount = 1;
    size_t idleAnimFrameDuration = 0;
    Vec2 idleAnimFrameSize = {26, 32};
    // RUN ANIMATION
    std::string runAnimPath = "bin/images/mario_run.png";
    size_t runAnimFrameCount = 3;
    size_t runAnimFrameDuration = 20;
    Vec2 runAnimFrameSize = {32, 32};
    // JUMP ANIMATION
    std::string jumpAnimPath = "bin/images/mario_jump.png";
    size_t jumpAnimFrameCount = 1;
    size_t jumpAnimFrameDuration = 0;
    Vec2 jumpAnimFrameSize = {32, 32};

    // SCENE LAYOUT
    Vec2 gridSize = {32, 32};
    Vec2 playerPosition = {0, 0};
};

#endif //GAMESCENESETTINGS_H

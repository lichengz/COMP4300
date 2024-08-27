//
// Created by white on 2024-08-23.
//

#include "Assets.h"

Assets::Assets() {
    m_playerIdleTexture.loadFromFile("bin/images/mario_idle.png");
    m_playerRunTexture.loadFromFile("bin/images/mario_run.png");
    m_playerJumpTexture.loadFromFile("bin/images/mario_jump.png");
    m_tileTexture.loadFromFile("bin/images/ground.png");
}

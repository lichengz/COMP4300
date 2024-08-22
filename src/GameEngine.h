//
// Created by white on 2024-08-18.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <utility>

#include "EntityManager.h"
#include "GameSettings.h"
#include "GuiManager.h"
#include "SFML/Graphics/Font.hpp"


class GameEngine {
    GameSettings settings;
    sf::RenderWindow m_window;
    sf::Font myFont;
    sf::Clock deltaClock;
    std::shared_ptr<GuiManager>  m_guiManager;
    std::shared_ptr<EntityManager> m_entityManager;
    int frameCounter = 0;

    void sUserInput();
    void sMovement();
    void sCollision();
    void sRender();
public:
    GameEngine(GameSettings settings);
    void start();
    void update();
    void initPlayer();
    void spawnEnemy();
    void shootBullet(Vec2 dir);
    void initWindow();
};



#endif //GAMEENGINE_H

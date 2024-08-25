//
// Created by white on 2024-08-18.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <utility>

#include "Assets.h"
#include "EntityManager.h"
#include "GameSettings.h"
#include "GuiManager.h"
#include "Scene.h"
#include "SFML/Graphics/Font.hpp"

typedef std::map<SceneType, std::shared_ptr<Scene>> SceneMap;

class GameEngine {
    GameSettings settings;
    sf::RenderWindow m_window;
    sf::Font myFont;
    sf::Clock deltaClock;
    std::shared_ptr<GuiManager>  m_guiManager;
    std::shared_ptr<EntityManager> m_entityManager;
    int frameCounter = 0;

    SceneType m_currentSceneType = SceneType::MENU;
    SceneMap m_sceneMap;
    size_t m_simulationSpeed = 1;
    bool m_running = true;

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

    sf::RenderWindow& getWindow();
    void changeScene(SceneType sceneType, bool endCurrentScene = false);
    void quit();
    const Assets& getAssets() const;
    const bool isRunning() const;
    const GameSettings& getSettings() const;
};



#endif //GAMEENGINE_H

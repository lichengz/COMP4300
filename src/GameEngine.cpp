//
// Created by white on 2024-08-18.
//

#include "GameEngine.h"

#include <imgui-SFML.h>
#include <iostream>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include <SFML/Window/Keyboard.hpp>

#include "GameScene.h"
#include "MenuScene.h"
#include "Utilities.h"

void GameEngine::sUserInput() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(m_window, event);

        if(event.type == sf::Event::Closed) {
            m_window.close();
        }

        if(event.type == sf::Event::KeyPressed) {
            std::cout << "Key Pressed: " << event.key.code << std::endl;
            if(m_sceneMap[m_currentSceneType]->getActionMap().contains(event.key.code)) {
                m_sceneMap[m_currentSceneType]->doAction(Action{m_sceneMap[m_currentSceneType]->getActionMap().at(event.key.code), ActionState::START});
            }
        }
        else if(event.type == sf::Event::KeyReleased) {
            if(m_sceneMap[m_currentSceneType]->getActionMap().contains(event.key.code)) {
                m_sceneMap[m_currentSceneType]->doAction(Action{m_sceneMap[m_currentSceneType]->getActionMap().at(event.key.code), ActionState::END});
            }
        }

        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                auto player = m_entityManager->getPlayer();
                if(player) {
                    // Get the pixel position of the mouse relative to the window
                    auto mousePos = sf::Mouse::getPosition(m_window);

                    // Convert the pixel position to world coordinates
                    auto worldPos = m_window.mapPixelToCoords(mousePos);

                    // Get the player's position
                    auto playerPos = player->getComponent<CTransform>().position;

                    // Calculate the direction
                    auto dir = Vec2{worldPos.x - playerPos.x, worldPos.y - playerPos.y};
                    dir = dir.normalize();
                    shootBullet(dir);
                }
            }
        }
    }
}

GameEngine::GameEngine(GameSettings settings): settings(std::move(settings)) {
    initWindow();
    m_entityManager = std::make_shared<EntityManager>();
    m_guiManager = std::make_shared<GuiManager>(m_window, m_entityManager);
    m_sceneMap[SceneType::GAME] = std::make_shared<GameScene>(this);
    m_sceneMap[SceneType::MENU] = std::make_shared<MenuScene>(this);
}

void GameEngine::start() {
    // initPlayer();
    if(!myFont.loadFromFile(settings.fontPath)) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }
    m_currentSceneType = SceneType::GAME;
    m_sceneMap[m_currentSceneType]->start();
}

void GameEngine::update() {
     while(m_window.isOpen()) {
         // m_guiManager->update(settings, m_window, deltaClock.restart());
         // m_entityManager->update();
         sUserInput();
         m_window.clear();
         m_sceneMap[m_currentSceneType]->update();
         m_sceneMap[m_currentSceneType]->render();
         m_window.display();
    }
}

void GameEngine::initPlayer() {
    // auto player = m_entityManager->addEntity({"player"});
    // float radius = settings.playerRadius;
    // int segments = settings.playerSegments;
    // float thickness = settings.playerOutlineThickness;
    // player-> cTransform = std::make_shared<CTransform>(Vec2{settings.windowWidth / 2.0f,settings.windowHeight / 2.0f}, Vec2{0.0f,0.0f});
    // player-> cName = std::make_shared<CName>("Player");
    // player-> cShape = std::make_shared<CShape>(std::make_shared<sf::CircleShape>(radius, segments));
    // player-> cShape->shape->setOrigin(radius, radius);
    // player-> cShape->shape->setFillColor(sf::Color::Transparent);
    // player-> cShape->shape->setOutlineColor(sf::Color::White);
    // player-> cShape->shape->setOutlineThickness(thickness); // Outline thickness of 5 units
    // player-> cBBox = std::make_shared<CBBox>(player, radius);
    // player->updateActions = { [player]() {
    //     player->cShape->shape->setRotation(player->cShape->shape->getRotation() + 1.0f);
    // }};
}

void GameEngine::spawnEnemy() {
    // auto enemy = m_entityManager->addEntity({"enemy"});
    // enemy-> cName = std::make_shared<CName>("Enemy");
    // float radius = Utilities::getRandomValue(settings.enemyMinRadius, settings.enemyMaxRadius);
    // int segments = Utilities::getRandomValue(settings.enemyMinSegments, settings.enemyMaxSegments);
    // enemy-> cShape = std::make_shared<CShape>(std::make_shared<sf::CircleShape>(radius, segments));
    // enemy-> cShape->shape->setOrigin(radius, radius);
    // enemy-> cShape->shape->setFillColor(sf::Color{static_cast<unsigned char>(Utilities::getRandomValue(0, 255)), static_cast<unsigned char>(Utilities::getRandomValue(0, 255)),static_cast<unsigned char>(Utilities::getRandomValue(0, 255))});
    // enemy-> cShape->shape->setOutlineColor(sf::Color::White);
    // enemy-> cShape->shape->setOutlineThickness(settings.playerOutlineThickness);
    // enemy-> cTransform = std::make_shared<CTransform>(Utilities::getRandomPosition(m_window, radius), Utilities::getRandomDirection() * settings.enemySpeed);
    // enemy-> cBBox = std::make_shared<CBBox>(enemy, radius);
    // enemy->updateActions = { [enemy, this]() {
    //     enemy->cShape->shape->setRotation(enemy->cShape->shape->getRotation() + 1.0f);
    //     for(const auto& bullet : m_entityManager->getEntitiesByTag("bullet")) {
    //         if(bullet->cBBox->intersects(*enemy->cBBox)) {
    //             m_entityManager->addTodestroy(bullet);
    //             m_entityManager->addTodestroy(enemy);
    //         }
    //     }
    // }};
}

void GameEngine::shootBullet(Vec2 dir) {
    // auto bullet = m_entityManager->addEntity({"bullet"});
    // bullet-> cTransform = std::make_shared<CTransform>(Vec2{0.0f,0.0}, dir * settings.bulletSpeed);
    // bullet-> cTransform->position = m_entityManager->getPlayer()->cTransform->position;
    // bullet-> cShape = std::make_shared<CShape>(std::make_shared<sf::CircleShape>(5.0f));
    // bullet-> cBBox = std::make_shared<CBBox>(bullet, 5.0f);
    // bullet->updateActions = { [bullet, this]() {
    //     auto color = bullet->cShape->shape->getFillColor();
    //     bullet->cShape->shape->setFillColor({color.r, color.g, color.b, static_cast<sf::Uint8>(std::max(0, color.a - 5))});
    //     if(color.a == 0) {
    //         m_entityManager->addTodestroy(bullet);
    //     }
    // }};
}

void GameEngine::initWindow() {
    m_window.create(sf::VideoMode(settings.windowWidth, settings.windowHeight), "SFML ImGui");
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
}

sf::RenderWindow & GameEngine::getWindow() {
    return m_window;
}

const GameSettings & GameEngine::getSettings() const {
    return settings;
}

//
// Created by white on 2024-08-18.
//

#ifndef GUIMANAGER_H
#define GUIMANAGER_H
#include "EntityManager.h"
#include "GameSettings.h"
#include "SFML/Graphics/RenderWindow.hpp"


class GuiManager {
    std::shared_ptr<EntityManager> m_entityManager;
public:
    GuiManager();
    GuiManager(sf::RenderWindow& window, const std::shared_ptr<EntityManager>& entityManager);
    void update(GameSettings& settings, sf::RenderWindow& window, const sf::Time& deltaTime);
};



#endif //GUIMANAGER_H

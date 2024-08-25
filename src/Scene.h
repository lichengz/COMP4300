//
// Created by white on 2024-08-23.
//

#ifndef SCENE_H
#define SCENE_H
#include <map>
#include <memory>

#include "Action.h"
#include "EntityManager.h"
#include "SFML/Window/Keyboard.hpp"

class GameEngine;
typedef std::map<sf::Keyboard::Key, ActionType> ActionMap;

enum class SceneType {
    GAME,
    MENU
};

class Scene {
protected:
    GameEngine* m_game = nullptr;
    EntityManager m_entityManager;
    ActionMap m_actionMap;
    bool m_paused = false;
    bool m_ended = false;
    size_t m_currentFrame = 0;

    virtual void onEnd() = 0;
    void setPaused(bool paused);

public:
    virtual ~Scene() = default;

    explicit Scene(GameEngine* game): m_game(game) {}

    virtual void start() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void doAction(const Action& action) = 0;

    void simulate(const size_t frames);
    void registerAction(sf::Keyboard::Key key, ActionType type);

    size_t width() const;
    size_t height() const;
    size_t currentFrame() const;

    bool hasEnded() const;
    const ActionMap& getActionMap() const;
    void drawLine(const Vec2& start, const Vec2& end);
};



#endif //SCENE_H

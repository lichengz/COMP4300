//
// Created by white on 2024-08-24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <deque>
#include <map>
#include <utility>

#include "Entity.h"
#include "GameSceneSettings.h"

enum class PlayerState {
    IDLE,
    RUN,
    JUMP,
    FALL,
    DEAD
};

enum class Direciton {
    LEFT,
    RIGHT
};

class Player {
    std::shared_ptr<Entity> m_playerEntity;
    std::map<PlayerState, std::shared_ptr<Animation>> m_animations;
    PlayerState m_state = PlayerState::IDLE;
    std::deque<Direciton> m_directionsStack;
    GameSceneSettings m_gameSceneSettings;
public:
    bool isGrounded = false;
    explicit Player(std::shared_ptr<Entity> playerEntity, const GameSceneSettings& settings) : m_playerEntity(std::move(playerEntity)), m_gameSceneSettings(settings) {
        // m_playerEntity->cTransform = std::make_shared<CTransform>(Vec2(0, 0), Vec2(0, 0));
        // m_playerEntity->cBBox = std::make_shared<CBBox>(m_playerEntity);
        // m_playerEntity->cRigidBody = std::make_shared<CRigidBody>(true);
        m_playerEntity->addComponent<CTransform>(Vec2(0, 0), Vec2(0, 0));
        m_playerEntity->addComponent<CBBox>(m_playerEntity);
        m_playerEntity->addComponent<CRigidBody>(true);
    }
    void addAnimation(PlayerState state, std::shared_ptr<Animation> animation);
    void setState(PlayerState state);
    std::shared_ptr<Entity>& getEntity() { return m_playerEntity; }
    void setPos(const Vec2& pos) {
        // m_playerEntity->cTransform->prevPosition = pos;
        // m_playerEntity->cTransform->position = pos;
        m_playerEntity->getComponent<CTransform>().prevPosition = pos;
        m_playerEntity->getComponent<CTransform>().position = pos;
    }
    Vec2 getPos() const {
        // return m_playerEntity->cTransform->position;
        return m_playerEntity->getComponent<CTransform>().position;
    }
    void setVel(const Vec2& vel) {
        // m_playerEntity->cTransform->velocity = vel;
        m_playerEntity->getComponent<CTransform>().velocity = vel;
    }
    Vec2 getVel() const {
        // return m_playerEntity->cTransform->velocity;
        return m_playerEntity->getComponent<CTransform>().velocity;
    }
    Vec2 getMaxSpriteSize() const;
    void moveLeft();

    void moveRight();

    void jump();

    void stop();

    void stopOneDirection(Direciton direction);

    void setFlipSprites(bool cond);

    void setPlayerHorizontalSpeed(Direciton direciton);

    void respawn();
};



#endif //PLAYER_H

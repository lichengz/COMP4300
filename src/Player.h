//
// Created by white on 2024-08-24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <utility>

#include "Entity.h"

enum class PlayerState {
    IDLE,
    RUN,
    JUMP,
    FALL,
    DEAD
};

class Player {
    std::shared_ptr<Entity> m_playerEntity;
    std::map<PlayerState, std::shared_ptr<Animation>> m_animations;
    PlayerState m_state = PlayerState::IDLE;
public:
    explicit Player(std::shared_ptr<Entity> playerEntity) : m_playerEntity(std::move(playerEntity)) {
        m_playerEntity->cTransform = std::make_shared<CTransform>(Vec2(0, 0), Vec2(0, 0));
        m_playerEntity->cBBox = std::make_shared<CBBox>(m_playerEntity);
    }
    void addAnimation(PlayerState state, std::shared_ptr<Animation> animation);
    void setState(PlayerState state);
    std::shared_ptr<Entity>& getEntity() { return m_playerEntity; }
    void setPos(const Vec2& pos) { m_playerEntity->cTransform->position = pos; }
    Vec2 getPos() const { return m_playerEntity->cTransform->position; }
    void setVel(const Vec2& vel) { m_playerEntity->cTransform->velocity = vel; }
    Vec2 getVel() const { return m_playerEntity->cTransform->velocity; }

    void moveLeft();

    void moveRight();

    void jump();

    void stop();
};



#endif //PLAYER_H

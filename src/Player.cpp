//
// Created by white on 2024-08-24.
//

#include "Player.h"

void Player::addAnimation(PlayerState state, std::shared_ptr<Animation> animation) {
    m_animations[state] = animation;
}

void Player::setState(PlayerState state) {
    if(m_animations.contains(state)) {
        m_state = state;
        m_playerEntity->cAnimation = m_animations[state];
    }
}

Vec2 Player::getMaxSpriteSize() const {
    Vec2 max = {0, 0};
    for(const auto& animation : m_animations) {
        max.x = std::max(max.x, animation.second->getSize().x);
        max.y = std::max(max.y, animation.second->getSize().y);
    }
    return max;
}

void Player::moveLeft() {
    m_directionsStack.push_back(Direciton::LEFT);
    setPlayerHorizontalSpeed(m_directionsStack.back());
}

void Player::moveRight() {
    m_directionsStack.push_back(Direciton::RIGHT);
    setPlayerHorizontalSpeed(m_directionsStack.back());
}

void Player::jump() {
    if(isGrounded) {
        // m_playerEntity->cTransform->velocity.y = -m_gameSceneSettings.playerJumpSpeed;
        m_playerEntity->getComponent<CTransform>().velocity.y = -m_gameSceneSettings.playerJumpSpeed;
    }
}

void Player::stop() {
    // m_playerEntity->cTransform->velocity.x = 0;
    m_playerEntity->getComponent<CTransform>().velocity.x = 0;
    setState(PlayerState::IDLE);
}

void Player::stopOneDirection(Direciton direction) {
    // m_directionsStack.erase(std::remove(m_directionsStack.begin(), m_directionsStack.end(), direction), m_directionsStack.end());
    for (auto it = m_directionsStack.begin(); it != m_directionsStack.end();) {
        if (*it == direction) {
            it = m_directionsStack.erase(it);  // Erase and get the next iterator
        } else {
            ++it;
        }
    }
    if(m_directionsStack.empty()) {
        stop();
    } else {
        setPlayerHorizontalSpeed(m_directionsStack.back());
    }
}

void Player::setFlipSprites(bool cond) {
    for(auto& animation : m_animations) {
        animation.second->getSprite().setScale(cond ? -1.0f : 1.0f, 1.0f);
    }
}

void Player::setPlayerHorizontalSpeed(Direciton direciton) {
    setState(PlayerState::RUN);
    switch (direciton) {
        case Direciton::LEFT:
            // m_playerEntity->cTransform->velocity.x = - m_gameSceneSettings.playerRunSpeed;
            m_playerEntity->getComponent<CTransform>().velocity.x = - m_gameSceneSettings.playerRunSpeed;
            setFlipSprites(true);
            break;
        case Direciton::RIGHT:
            //m_playerEntity->cTransform->velocity.x = m_gameSceneSettings.playerRunSpeed;
            m_playerEntity->getComponent<CTransform>().velocity.x = m_gameSceneSettings.playerRunSpeed;
            setFlipSprites(false);
            break;
    }
}

void Player::respawn() {

}

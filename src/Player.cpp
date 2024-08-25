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

void Player::moveLeft() {
    m_playerEntity->cTransform->velocity.x = -1;
}

void Player::moveRight() {
    m_playerEntity->cTransform->velocity.x = 1;
}

void Player::jump() {
}

void Player::stop() {
    m_playerEntity->cTransform->velocity.x = 0;
}

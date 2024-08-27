//
// Created by white on 2024-08-23.
//

#include "Animation.h"

#include "Entity.h"

void Animation::update() {
    // Set Position
    m_sprite.setPosition(m_entity->getComponent<CTransform>().position.x, m_entity->getComponent<CTransform>().position.y);
    // Set Frame
    m_frameIndex = m_frameIndex % m_frameCount;
    m_sprite.setTextureRect(sf::IntRect(m_frameIndex * m_frameSize.x, 0, m_frameSize.x, m_frameSize.y));
    if(m_frameDuration != 0 && m_frameCount > 1) {
        m_currentFrame = (m_currentFrame + 1) % m_frameDuration;
        if(m_currentFrame == 0) {
            m_frameIndex++;
        }
    }

}

bool Animation::hasEnded() const {
    return m_currentFrame >= m_frameCount;
}

const Vec2 & Animation::getSize() const {
    return m_frameSize;
}

 sf::Sprite & Animation::getSprite()  {
    return m_sprite;
}

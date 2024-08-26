//
// Created by white on 2024-08-20.
//

#include "Utilities.h"

#include "Entity.h"

Vec2 Utilities::getRandomVec(Vec2 xRange, Vec2 yRange) {
    return Vec2(getRandomValue(xRange.x, xRange.y), getRandomValue(yRange.x, yRange.y));
}

Vec2 Utilities::getRandomPosition(const sf::RenderWindow &window, float padding) {
    return getRandomVec({padding, static_cast<float>(window.getSize().x) - padding}, {padding, static_cast<float>(window.getSize().y) - padding});
}

Vec2 Utilities::getRandomDirection() {
    return getRandomVec({-100, 100}, {-100, 100}).normalize();
}

Vec2 Utilities::getOverlap(const std::shared_ptr<CBBox> &a, const std::shared_ptr<CBBox> &b) {
    float xDist = std::abs(a->m_entity->cTransform->position.x - b->m_entity->cTransform->position.x);
    float x = std::max(a->m_entity->cBBox->getBBox().x + b->m_entity->cBBox->getBBox().x - xDist, 0.0f);
    float yDist = std::abs(a->m_entity->cTransform->position.y - b->m_entity->cTransform->position.y);
    float y = std::max(a->m_entity->cBBox->getBBox().y + b->m_entity->cBBox->getBBox().y - yDist, 0.0f);
    return {x, y};
}

Vec2 Utilities::getPrevOverlap(const std::shared_ptr<CBBox> &a, const std::shared_ptr<CBBox> &b) {
    float xDist = std::abs(a->m_entity->cTransform->prevPosition.x - b->m_entity->cTransform->prevPosition.x);
    float x = std::max(a->m_entity->cBBox->getBBox().x + b->m_entity->cBBox->getBBox().x - xDist, 0.0f);
    float yDist = std::abs(a->m_entity->cTransform->prevPosition.y - b->m_entity->cTransform->prevPosition.y);
    float y = std::max(a->m_entity->cBBox->getBBox().y + b->m_entity->cBBox->getBBox().y - yDist, 0.0f);
    return {x, y};
}

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

Vec2 Utilities::getOverlap(const CBBox &a, const CBBox &b) {
    float xDist = std::abs(a.m_entity->getComponent<CTransform>().position.x - b.m_entity->getComponent<CTransform>().position.x);
    float x = std::max(a.m_entity->getComponent<CBBox>().getBBox().x + b.m_entity->getComponent<CBBox>().getBBox().x - xDist, 0.0f);
    float yDist = std::abs(a.m_entity->getComponent<CTransform>().position.y - b.m_entity->getComponent<CTransform>().position.y);
    float y = std::max(a.m_entity->getComponent<CBBox>().getBBox().y + b.m_entity->getComponent<CBBox>().getBBox().y - yDist, 0.0f);
    return {x, y};
}

Vec2 Utilities::getPrevOverlap(const CBBox &a, const CBBox &b) {
    float xDist = std::abs(a.m_entity->getComponent<CTransform>().prevPosition.x - b.m_entity->getComponent<CTransform>().prevPosition.x);
    float x = std::max(a.m_entity->getComponent<CBBox>().getBBox().x + b.m_entity->getComponent<CBBox>().getBBox().x - xDist, 0.0f);
    float yDist = std::abs(a.m_entity->getComponent<CTransform>().prevPosition.y - b.m_entity->getComponent<CTransform>().prevPosition.y);
    float y = std::max(a.m_entity->getComponent<CBBox>().getBBox().y + b.m_entity->getComponent<CBBox>().getBBox().y - yDist, 0.0f);
    return {x, y};
}

Vec2 Utilities::getDirectionToCollision(const CTransform &a, const CTransform &b) {
    float x = 0;
    if(a.position.x < b.position.x) {
        x = -1;
    } else if(a.position.x > b.position.x) {
        x = 1;
    }
    float y = 0;
    if(a.position.y < b.position.y) {
        y = -1;
    } else if(a.position.y > b.position.y) {
        y = 1;
    }
    return Vec2{x, y};
}

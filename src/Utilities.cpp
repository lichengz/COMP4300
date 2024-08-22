//
// Created by white on 2024-08-20.
//

#include "Utilities.h"

Vec2 Utilities::getRandomVec(Vec2 xRange, Vec2 yRange) {
    return Vec2(getRandomValue(xRange.x, xRange.y), getRandomValue(yRange.x, yRange.y));
}

Vec2 Utilities::getRandomPosition(const sf::RenderWindow &window, float padding) {
    return getRandomVec({padding, static_cast<float>(window.getSize().x) - padding}, {padding, static_cast<float>(window.getSize().y) - padding});
}

Vec2 Utilities::getRandomDirection() {
    return getRandomVec({-100, 100}, {-100, 100}).normalize();
}

//
// Created by white on 2024-08-20.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include "Vec2.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <random>

#include "Components.h"


class Utilities {
public:
    template<typename T>
    static T getRandomValue(T min, T max);
    static Vec2 getRandomVec(Vec2 xRange, Vec2 yRange);
    static Vec2 getRandomPosition(const sf::RenderWindow& window, float pclose = 0.0f);
    static Vec2 getRandomDirection();
    static Vec2 getOverlap(const CBBox &a, const CBBox &b);
    static Vec2 getPrevOverlap(const CBBox &a, const CBBox &b);
    static Vec2 getDirectionToCollision(const CTransform &a, const CTransform &b);
};

template<typename T>
T Utilities::getRandomValue(T min, T max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return static_cast<T>(dist(gen));
}

#endif //UTILITIES_H

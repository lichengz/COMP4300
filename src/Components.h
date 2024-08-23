//
// Created by white on 2024-08-17.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "Vec2.h"
#include "SFML/Graphics/Shape.hpp"

class Transform{};

class CTransform : public Transform {
public:
    Vec2 position = {0, 0};
    Vec2 velocity = {0, 0};
    Vec2 size = {0, 0};
    float angle = 0;
};

class CName : public Transform {
public:
    std::string name;
};

class CShape : public Transform {
public:
    std::shared_ptr<sf::Shape> shape;
};

class CBBox : public Transform {
public:
    CTransform& cTransform;
    float boundingRadius;
    bool intersects(const CBBox& other) {
        return boundingRadius + other.boundingRadius > cTransform.position.distance(other.cTransform.position);
    }
};

#endif //COMPONENTS_H

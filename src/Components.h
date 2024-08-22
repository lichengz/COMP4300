//
// Created by white on 2024-08-17.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "Vec2.h"
#include "SFML/Graphics/Shape.hpp"

class CTransform {
public:
    Vec2 position;
    Vec2 velocity;
};

class CName {
public:
    std::string name;
};

class CShape {
public:
    std::shared_ptr<sf::Shape> shape;
};

class CBBox {
public:
    CTransform& cTransform;
    float boundingRadius;
    bool intersects(const CBBox& other) {
        return boundingRadius + other.boundingRadius > cTransform.position.distance(other.cTransform.position);
    }
};

#endif //COMPONENTS_H

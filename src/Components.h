//
// Created by white on 2024-08-17.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <memory>
#include <string>

#include "Vec2.h"
#include "SFML/Graphics/Shape.hpp"

class Entity;

class Transform {
public:
    bool has = false;
};

class CTransform : public Transform {
public:
    Vec2 position = {0, 0};
    Vec2 prevPosition = {0, 0};
    Vec2 velocity = {0, 0};
    Vec2 size = {0, 0};
    float angle = 0;
    CTransform() = default;
    CTransform(Vec2 position, Vec2 velocity) : position(position), velocity(velocity) {}
    CTransform(Vec2 position, Vec2 velocity, Vec2 size, float angle) : position(position), velocity(velocity), size(size), angle(angle) {}
};

class CName : public Transform {
public:
    std::string name;
    CName() = default;
    explicit CName(std::string name) : name(name) {}
};

class CShape : public Transform {
public:
    std::shared_ptr<sf::Shape> shape;
    CShape() = default;
    explicit CShape(std::shared_ptr<sf::Shape> shape) : shape(shape) {}
};

class CBBox : public Transform {
    float m_radius = 0;
public:
    std::shared_ptr<Entity> m_entity;
    float boundingRadius() const;
    bool intersects(const CBBox& other) const;
    Vec2 getBBox() const;
    CBBox() = default;
    explicit CBBox(const std::shared_ptr<Entity>& entity, float radius = 0) : m_entity(entity), m_radius(radius) {}
};

class CRigidBody : public Transform {
public:
    bool isGravity = false;
    CRigidBody() = default;
    explicit CRigidBody(bool isGravity) : isGravity(isGravity) {}
};

#endif //COMPONENTS_H

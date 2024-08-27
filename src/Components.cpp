//
// Created by white on 2024-08-24.
//

#include "Components.h"

#include "Entity.h"

float CBBox::boundingRadius() const {
    if(m_entity->hasComponent<Animation>()) {
        return m_entity->getComponent<Animation>().getSize().x / 2;
    }
    return m_radius;
}

bool CBBox::intersects(const CBBox &other) const {
    return boundingRadius() + other.boundingRadius() >m_entity->getComponent<CTransform>().position.distance(other.m_entity->getComponent<CTransform>().position);
}

Vec2 CBBox::getBBox() const {
    if(m_entity->hasComponent<Animation>()) {
        return m_entity->getComponent<Animation>().getSize() / 2;
    }
    return {m_radius, m_radius};
}

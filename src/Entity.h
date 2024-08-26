//
// Created by white on 2024-08-17.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Animation.h"
#include "Components.h"

class Entity {
    const size_t m_id = 0;
    // std::string m_tag = "Default";
    std::vector<std::string> m_tags;
    bool m_active = true;
public:
    friend class EntityManager;
    friend class GuiManager;
    Entity() = default;
    Entity(size_t id, std::vector<std::string> tags, bool active) : m_id(id), m_tags(tags), m_active(active) {};
    std::vector<std::function<void()>> updateActions;
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CName> cName;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CBBox> cBBox;
    std::shared_ptr<CRigidBody> cRigidBody;
    std::shared_ptr<Animation> cAnimation;
    void update();
    bool& isActive() {
        return m_active;
    }
    std::vector<std::string>& getTags() {
        return m_tags;
    }
    size_t getId() const {
        return m_id;
    }
};

#endif //ENTITY_H

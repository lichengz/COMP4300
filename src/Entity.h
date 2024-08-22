//
// Created by white on 2024-08-17.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "Components.h"

class Entity {
    const size_t m_id = 0;
    std::string m_tag = "Default";
    bool m_active = true;
    Entity() = default;
    Entity(size_t id, std::string tag, bool active) : m_id(id), m_tag(tag), m_active(active) {};
public:
    friend class EntityManager;
    friend class GuiManager;
    std::vector<std::function<void()>> updateActions;
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CName> cName;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CBBox> cBBox;
    void update();
    bool& isActive() {
        return m_active;
    }
    std::string& getTag() {
        // std::cout << m_tag << std::endl;
        return m_tag;
    }
};

#endif //ENTITY_H

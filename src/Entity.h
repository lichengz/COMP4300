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

typedef std::tuple<CTransform, CName, CShape, CBBox, CRigidBody, Animation> ComponentTuple;

class Entity {
    const size_t m_id = 0;
    // std::string m_tag = "Default";
    std::vector<std::string> m_tags;
    bool m_active = true;
    ComponentTuple m_components;
    Entity(size_t id, std::vector<std::string> tags, bool active) : m_id(id), m_tags(tags), m_active(active) {};
public:
    friend class EntityManager;
    friend class GuiManager;
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

    template <typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    const T& getComponent() const
    {
        return std::get<T>(m_components);
    }

    // Parameter packing. && means it's an r-value reference
    // Ex: entity->addComponent<CTransform>(Vec2(100, 100), Vec2(5, 5));
    // Ex: entity->addComponent<CInput>();
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        auto& component = getComponent<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
        return component;
    }

    template <typename T>
    bool hasComponent() const
    {
        return getComponent<T>().has;
    }

    template <typename T>
    void removeComponent()
    {
        auto& component = getComponent<T>();
        component = T();
        component.has = false;
    }
};

#endif //ENTITY_H

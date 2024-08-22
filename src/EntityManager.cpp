//
// Created by white on 2024-08-17.
//

#include "EntityManager.h"

#include <iostream>

EntityManager::EntityManager() {
}

void EntityManager::update() {
    if(!m_entitiesToDestroy.empty()) {
        for(auto& entity : m_entitiesToDestroy) {
            destroy(entity);
        }
        m_entitiesToDestroy.clear();
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    std::shared_ptr<Entity> entity;
    if(!m_entitiesBackUp.empty()) {
        entity = std::move(m_entitiesBackUp.back());
        m_entitiesBackUp.pop_back();
        entity->m_tag = tag;
        entity->m_active = true;
    }else {
        entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag, true));
    }
    m_entities.push_back(entity);
    if(!m_entityMap.contains(tag)) {
        m_entityMap[tag] = EntityVec();
    }
    m_entityMap[tag].push_back(entity);

    return entity;
}

const EntityVec & EntityManager::getEntities() {
    return m_entities;
}

const EntityVec & EntityManager::getEntitiesByTag(const std::string &tag) {
    return m_entityMap[tag];
}

const EntityMap & EntityManager::getEntityMap() {
    return m_entityMap;
}

const std::shared_ptr<Entity> EntityManager::getPlayer() {
    auto playerVec = getEntitiesByTag("player");
    if(playerVec.empty()) {
        std::cerr << "No player entity found" << std::endl;
        return nullptr;
    }else if(playerVec.size() > 1) {
        std::cerr << "Multiple player entities found" << std::endl;
        return nullptr;
    }
    return getEntitiesByTag("player")[0];
}

void EntityManager::destroy(const std::shared_ptr<Entity>& entity) {
    // Remove the entity from m_entities
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());

    // Remove the entity from the map of entities by tag
    auto it_map = m_entityMap.find(entity->getTag());
    if (it_map != m_entityMap.end()) {
        auto& entityList = it_map->second;
        entityList.erase(std::remove(entityList.begin(), entityList.end(), entity), entityList.end());
    }

    // Backup the entity and deactivate it
    m_entitiesBackUp.push_back(entity);
    entity->m_active = false;
    entity->updateActions.clear();
}

void EntityManager::addTodestroy(const std::shared_ptr<Entity> &entity) {
    m_entitiesToDestroy.push_back(entity);
}

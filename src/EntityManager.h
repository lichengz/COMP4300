//
// Created by white on 2024-08-17.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>
#include <memory>
#include <vector>

#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
    EntityVec m_entities;
    EntityVec m_entitiesBackUp;
    EntityVec m_entitiesToAdd;
    EntityVec m_entitiesToDestroy;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;
public:
    EntityManager();
    void update();
    // std::shared_ptr<Entity> addEntity(const std::string& tag);
    std::shared_ptr<Entity> addEntity(const std::vector<std::string>& tag);
    const EntityVec& getEntities();
    const EntityVec& getEntitiesByTag(const std::string& tag);
    const EntityMap& getEntityMap();
    const std::shared_ptr<Entity> getPlayer();
    void destroy(const std::shared_ptr<Entity>& entity);
    void addTodestroy(const std::shared_ptr<Entity>& entity);

};



#endif //ENTITYMANAGER_H

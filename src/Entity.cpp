//
// Created by white on 2024-08-17.
//
#include "Entity.h"

void Entity::update() {
    if(isActive()) {
        for(auto &action : updateActions) {
            action();
        }
    }
}

#include "ECS.hpp"
#include "../Logger/Logger.hpp"
#include <cassert>

int Entity::GetId() const {
    return id;
}

void System::AddEntity(Entity entity)
{
    entities.push_back(entity);
}

void System::RemoveEntity(size_t entityIndex)
{
    // NOTE: this is an unordered remove
    int lastIndex = entities.size() - 1;   

    Entity temp = entities[lastIndex];
    entities[lastIndex] = entities[entityIndex];
    entities[entityIndex] = temp;

    entities.pop_back();
}

void System::RemoveEntity(const Entity& entity)
{
    // NOTE: this is an unordered remove
    int lastIndex = entities.size() - 1;
    int targetIndex = -1;

    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i] == entity) {
            targetIndex = i;
            break;
        }
    }

    assert(targetIndex != -1 && "The entity to be removed was not found!");

    Entity temp = entities[lastIndex];
    entities[lastIndex] = entity;
    entities[targetIndex] = temp;

    entities.pop_back();
}

const std::vector<Entity>& System::GetEntities() const
{
    return entities;
}

Signature System::GetComponentSignature() const
{
    return componentSignature;
}


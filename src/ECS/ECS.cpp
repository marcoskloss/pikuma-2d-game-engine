#include "ECS.hpp"
#include "Logger/Logger.hpp"

int Entity::GetId() const {
    return id;
}

void System::AddEntity(Entity entity)
{
    entities.push_back(entity);
}

void System::RemoveEntity(const Entity& entity)
{
    int entityId = entity.GetId();
    entities.erase(std::remove_if(entities.begin(), entities.end(), [entityId](Entity other) {
        return entityId == other.GetId();
    }), entities.end());
}

const std::vector<Entity>& System::GetEntities() const
{
    return entities;
}

Signature System::GetComponentSignature() const
{
    return componentSignature;
}

Entity Registry::CreateEntity()
{
    int entityId = numEntities++;
    Entity entity = Entity(entityId);
    entitiesToBeAdded.insert(entity);
    Logger::Log("Entity created with ID " + std::to_string(entityId));
    return entity;
}

void Registry::Update()
{
}
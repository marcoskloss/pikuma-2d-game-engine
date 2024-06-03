#pragma once

#include <bitset>
#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS = 32;

// To keep track of witch components an entity has,
// also, to keep track witch entites a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

// Used to assign a unique id to a component type
template <typename T>
class Component : public IComponent {
    public:
        static int GetId()
        {
            static int id = nextId++;
            return id;
        }
};

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id) {};
        int GetId() const;

        bool operator ==(const Entity& other) const {
            return id == other.GetId();
        }

        bool operator !=(const Entity& other) const {
            return id != other.GetId();
        }
};

class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntity(Entity entity);
        void RemoveEntity(Entity entity);
        const std::vector<Entity>& GetEntities() const;
        Signature GetComponentSignature() const;
        void RemoveEntity(const Entity& entity);
        void RemoveEntity(size_t entityIndex);

        template<typename T> void RequireComponent();
};


template <typename T>
void System::RequireComponent()
{
    int componentId = Component<T>::GetId();
    componentSignature.set(componentId);
}


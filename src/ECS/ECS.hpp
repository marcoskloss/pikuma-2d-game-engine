#pragma once

#include <bitset>
#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

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
            return this->id == other.GetId();
        }

        bool operator !=(const Entity& other) const {
            return this->id != other.GetId();
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
        void RemoveEntity(const Entity& entity);
        const std::vector<Entity>& GetEntities() const;
        Signature GetComponentSignature() const;

        template<typename T> void RequireComponent();
};

class IPool {
    public:
        virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(int size = 100) {
            data.resize(size);
        }
        ~Pool() = default;

        bool IsEmpty() const { return data.empty(); }

        int GetSize() const { return data.size(); }

        void Resize(int n) { data.resize(n); }

        void Clear() { data.clear(); }
 
        void Set(int index, T obj) { data[index] = obj; }

        T& Get(int index) { 
            return static_cast<T&>(data[index]);
        }
};

// Manages all the entities in the game scene, coordinates everything
class Registry {
    private:
        int numEntities = 0;
        // Each Pool contains all the data for a certain component type
        // Vector index = component type id
        // Pool index = entity id
        std::vector<IPool*> componentPools;

        // Vector of component signature per entity, saying which component is turned `on` for a given entity
        // Vector index = entity id
        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, System*> systems;

        // Set of entities that are flagged to be added or removed in the next registry Update()
        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeKilled;

    public:
        Registry() = default;
        void Update();
        Entity CreateEntity();
        void AddComponent();
        void AddEntityToSystem(Entity entity);
};

template <typename T>
void System::RequireComponent()
{
    const auto componentId = Component<T>::GetId();
    printf("COMPONENT_ID: %d\n", componentId);
    componentSignature.set(componentId);
}


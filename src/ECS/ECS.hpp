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
            data.resize(100);
        }

        virtual ~Pool() = default;

        bool isEmpty() const { return data.empty(); }

        int GetSize(int size) const { return data.size(); }

        void Resize(int n) { data.resize(n); }

        void Clear() { data.clear(); }

        void Add(T obj) { data.push_back(obj); }

        void Set(int index, T obj) { data[index] = obj; }

        T Get(int index) const { return data[index]; }

        T operator [](unsigned int index) { return data[index]; }
};


class Registry {
    private:
        int numEntities = 0;

        // Each pool contains all the data for a certain component type
        // Vector index = component type id
        // Pool index = entity id
        std::vector<IPool*> componentPools;

        // component signatures per entity, saying which component is turned on for a given entity
        // Vector index = entity id
        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, System*> systems;

    public:
        Registry() = default;

        // TODO
        // CreateEntity()
        // DestroyEntity()

        // AddComponent(entity)
        // RemoveComponent(entity)
        // HasComponent(entity)
        
        // AddSystem()
        // RemoveSystem()
        // HasSystem()
        // GetSystem()
};


template <typename T>
void System::RequireComponent()
{
    int componentId = Component<T>::GetId();
    componentSignature.set(componentId);
}




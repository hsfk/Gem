#pragma once

#include <list>
#include "Scene/Scene.h"

struct World;

class Entity : public Transformable
{
public:
        enum Action
        {
                aeaReset,
                aeaDispose
        };

        virtual Action invalidate(Scene& scene, World& world)
        {
                return aeaReset;
        }
};

class World : public Serial
{
public:
        World(Scene& scene);
        void invalidate();
        void loadEntity(Entity* e);

        uint64_t counter;

        DECLARE_SERIAL(World)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

protected:
        typedef std::list<Index> EntityList;

        Scene&        scene;
        EntityList entities;
};

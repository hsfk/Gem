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

        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Entity)
};

class World : public Serial
{
public:
        World();
        void clear();
        void invalidate(Scene& scene);
        void loadEntity(Entity* e, Scene& scene);

        uint64_t counter;


        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(World)

protected:
        typedef std::list<Index> EntityList;

        EntityList entities;
};

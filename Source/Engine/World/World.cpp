#include "World.h"

void Entity::save(Ostream& out) const
{
        Transformable::save(out);
}

void Entity::load(Istream& in)
{
        Transformable::load(in);
}

World::World()
        : counter(0)
{
}

void World::clear()
{
        entities.clear();
        counter = 0;
}

void World::invalidate(Scene& scene)
{
        size_t size = entities.size();
        for (size_t i = 0; i < size; i++)
        {
                Index node = entities.front();
                entities.pop_front();
                Entity& e = reinterpret_cast<Entity&>(scene.getNode(node));
                Entity::Action act = e.invalidate(scene, *this);
                if (act == Entity::Action::aeaDispose)
                        ;
                else
                        entities.push_back(node);
        }
        counter++;
}

void World::loadEntity(Entity* e, Scene& scene)
{
        Index node = scene.loadNode(e);
        e->setLocation(node);
        entities.push_back(node);
}

void World::save(Ostream& out) const
{
        out < counter < entities.size();
        for (EntityList::const_iterator it = entities.cbegin(); it != entities.cend(); it++)
                out < *it;
}
void World::load(Istream& in)
{
        in > counter;
        size_t size = in.read<size_t>();
        for (size_t i = 0; i < size; i++)
                entities.push_back(in.read<Index>());
}

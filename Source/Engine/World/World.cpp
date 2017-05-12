#include "World.h"

World::World(Scene& scene)
        : scene(scene), counter(0)
{
}

void World::invalidate()
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

void World::loadEntity(Entity* e)
{
        Index node = scene.loadNode(e);
        e->setLocation(node);
        entities.push_back(node);
}

void World::save(Ostream& out) const
{
        out < entities.size();
        for (EntityList::const_iterator it = entities.cbegin(); it != entities.cend(); it++)
                out < *it;
}
void World::load(Istream& in)
{
        size_t size;
        in > size;
        for (size_t i = 0; i < size; i++)
        {
                Index e;
                in > e;
                entities.push_back(e);
        }
}

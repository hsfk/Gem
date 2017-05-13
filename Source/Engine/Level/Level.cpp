#include "Level.h"

Level::Level()
        : player(-1), renderer(nullptr)
{
}

void Level::clear()
{
        scene.clear();
        world.clear();

        delete renderer;
        renderer = nullptr;
}

void Level::initialize()
{
}

void Level::invalidate()
{
        world.invalidate(scene);
}

void Level::render()
{
        jassert(renderer);
        renderer->render(scene, getPlayer().cam);
}

Actor& Level::getPlayer()
{
        jassert(player != -1);
        return reinterpret_cast<Actor&>(scene.getNode(player));
}

void Level::setPlayer(Actor* player)
{
        this->player = scene.loadNode(player);
}

void Level::save(Ostream& out) const
{
        out << scene << world << *renderer < player;
}

void Level::load(Istream& in)
{
        clear();
        in >> scene >> world >> (void**)&renderer > player;
}

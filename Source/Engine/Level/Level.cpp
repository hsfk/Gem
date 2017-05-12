#include "Level.h"

Level::Level()
        : world(scene), player(nullptr)
{
}

void Level::initialize()
{
}

void Level::invalidate()
{
        world.invalidate();
}

void Level::render()
{
        jassert(renderer);
        renderer->render(scene, player->cam);
}

Actor* Level::getPlayer()
{
        jassert(player);
        return player;
}

void Level::save(Ostream& out) const
{
        out << scene << world << static_cast<const Serial&>(static_cast<Transformable&>(*player));
}

void Level::load(Istream& in)
{
        in >> scene >> world >> (void**)&player;
}

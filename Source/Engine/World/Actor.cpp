#include "Actor.h"

Actor::Actor(const Camera& cam)
        : cam(cam)
{
}

void Actor::setPos(const Point3D& pos)
{
        cam.setPos(pos);
        Entity::setPos(pos);
}

void Actor::move(const Vec3D& delta)
{
        cam.moveWithTarget(delta);
        Entity::move(delta);
}

void Actor::rotate(Angle3D angle)
{
        cam.rotate(angle);
}

void Actor::save(Ostream& out) const
{
        Entity::save(out);
        out << cam;
}

void Actor::load(Istream& in)
{
        Entity::load(in);
        in >> cam;
}

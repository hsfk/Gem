#include "Transformable.h"
#include "Math.h"

Placement::Placement()
{
}

Placement::Placement(const Placement& p)
        : Placement(p.pos)
{
}

Placement::Placement(const Point3D& p)
        : pos(p)
{
}

void Placement::setPos(const Point3D& pos)
{
        setDirty();
        this->pos = pos;
}

void Placement::move(const Vec3D& delta)
{
        setPos(pos + delta);
}

Mat4D Placement::getTransformMatrix() const
{
        return glm::translate(Mat4D(), pos);
}

Point3D Placement::getPos() const
{
        return pos;
}

void Placement::save(Ostream& out) const
{
        SceneNode::save(out);
        out < pos;
}

void Placement::load(Istream& in)
{
        SceneNode::load(in);
        in > pos;
}

Transformable::Transformable(const Point3D& pos)
        : Placement(pos), stretch(Vec3D(1, 1, 1))
{
}

Mat4D Transformable::getTransformMatrix() const
{
        return Placement::getTransformMatrix() * glm::scale(stretch);
}

void Transformable::setStretch(const Vec3D& stretch)
{
        setDirty();
        this->stretch = stretch;
}

Vec3D Transformable::getStretch() const
{
        return stretch;
}

void Transformable::save(Ostream& out) const
{
        Placement::save(out);
        out < stretch;
}

void Transformable::load(Istream& in)
{
        Placement::load(in);
        in > stretch;
}

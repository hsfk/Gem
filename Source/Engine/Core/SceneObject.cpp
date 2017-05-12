#include "SceneObject.h"

SceneNode::SceneNode()
        : binding(0), location(0), dirty(false)
{
}

Mat4D SceneNode::getTransformMatrix() const
{
        return Mat4D();
}

Index SceneNode::getBinding() const
{
        return binding;
}

void SceneNode::bind(Index i)
{
        setDirty();
        binding = i;
}

void SceneNode::bind(const SceneNode& other)
{
        bind(other.getLocation());
}

Index SceneNode::getLocation() const
{
        return location;
}

void SceneNode::setLocation(Index loc)
{
        location = loc;
}

bool SceneNode::isDirty() const
{
        return dirty;
}

void SceneNode::setDirty() const
{
        dirty = true;
}

void SceneNode::setClean() const
{
        dirty = false;
}

void SceneNode::save(Ostream& out) const
{
        SceneObject::save(out);
        out < binding;
}

void SceneNode::load(Istream& in)
{
        SceneObject::load(in);
        in > binding;
}

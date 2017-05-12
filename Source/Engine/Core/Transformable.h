#pragma once

#include "Types.h"
#include "SceneObject.h"

class Placement : public SceneNode
{
public:
        Placement();
        Placement(const Placement& p);
        Placement(const Point3D& p);

        virtual void  setPos(const Point3D& pos);
        virtual void  move(const Vec3D& delta);
        virtual Mat4D getTransformMatrix() const override;
        Point3D       getPos() const;

        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Placement)

private:
        Point3D pos;
};

//class Orientation : public Placement
//{
//public:
//
//        Angle3D orientation;
//
//        virtual void save(Ostream& out) const override;
//        virtual void load(Istream& in) override;
//        SERIAL_DECLARE_TYPEINFO(Placement)
//};

class Transformable : public Placement
{
public:
        Transformable(const Point3D& pos = Point3D(0, 0, 0));
        virtual Mat4D getTransformMatrix() const override;

        virtual void setStretch(const Vec3D& stretch);
        Vec3D        getStretch() const;

        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Transformable)

private:
        Vec3D stretch;
};

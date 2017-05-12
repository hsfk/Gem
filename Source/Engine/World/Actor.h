#pragma once

#include "World.h"

class Actor : public Entity
{
public:
        Actor() = default;
        Actor(const Camera& cam);

        virtual void setPos(const Point3D& pos) override;
        virtual void move(const Vec3D& delta) override;
        void rotate(Angle3D angle);

        DECLARE_SERIAL(Actor)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

        Camera cam;
};


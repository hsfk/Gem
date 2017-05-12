#pragma once

#include "Core/Transformable.h"

enum ModelRenderType
{
        mrtNone,
        mrtEdges,
        mrtSolid,
        mrtLitSolid,
        mrtTextured,
        mrtLitTextured,

        mrtSize
};

struct Model : public Transformable
{
        Model();
        Model(const Point3D& pos, Index mesh);
        Model(Index mesh);

        Index mesh;
        enum ModelRenderType renderType;

        DECLARE_SERIAL(Model)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
};

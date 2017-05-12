#include "Model.h"

Model::Model()
        : Model(Point3D(0, 0, 0), Index())
{
}

Model::Model(const Point3D& pos, Index mesh)
        : Transformable(pos), mesh(mesh), renderType(mrtNone)
{
}

Model::Model(Index mesh)
        : Model(Point3D(0, 0, 0), mesh)
{
        renderType = mrtEdges;
}

void Model::save(Ostream& out) const
{
        Transformable::save(out);
        out < mesh < renderType;
}

void Model::load(Istream& in)
{
        Transformable::load(in);
        in > mesh > renderType;
}

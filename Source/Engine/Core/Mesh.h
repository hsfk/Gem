#pragma once

#include "Buffer.h"
#include "SceneObject.h"

struct Mesh : public Serial
{
        Mesh();
        Mesh(Index mat, const Vertices& vert, const Normals& norm
                , const TextureCoords& uv
                , const Indices& indices);
        Mesh(const Vertices& vert, const Indices& indices);
        Mesh(const Vertices& vert, const Indices& indices, const Normals& normals);

        Mesh(const Mesh& other);
        Mesh(Mesh&& other);
        Mesh& operator=(const Mesh& other);

        Index         material;
        Vertices      vertices;
        Normals       normals;
        TextureCoords texCoords;
        Indices       indices; // vertex indices

        static Mesh fromRectangle(Point3D p1, Point3D p2, Point3D p3, Point3D p4, Vec3D norm);

        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Mesh)
};

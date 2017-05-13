#include "Mesh.h"
#include "Scene/Package.h" // default material

Mesh::Mesh()
        : material(Package::defaultMaterialIndex)
{
}

Mesh::Mesh(Index mat, const Vertices& vert, const Normals& norm, const TextureCoords& uv, const Indices& indices)
        : material(mat), vertices(vert), normals(norm), texCoords(uv), indices(indices)
{
}

Mesh::Mesh(const Vertices& vert, const Indices& indices)
        : Mesh(Package::defaultMaterialIndex, vert, Normals(), TextureCoords(), indices)
{
}

Mesh::Mesh(const Vertices& vert, const Indices& indices, const Normals& normals)
        : Mesh(vert, indices)
{
        this->normals = normals;
}

Mesh::Mesh(const Mesh& other)
        : Mesh(other.material, other.vertices, other.normals, other.texCoords, other.indices)
{
}

Mesh::Mesh(Mesh&& other)
        : Mesh(other.material, Vertices(), Normals(), TextureCoords(), Indices())
{
        vertices.swap(other.vertices);
        normals.swap(other.normals);
        texCoords.swap(other.texCoords);
        indices.swap(other.indices);
}

Mesh& Mesh::operator=(const Mesh& other)
{
        material = other.material;
        indices  = other.indices;
        return *this;
}

Mesh Mesh::fromRectangle(Point3D p1, Point3D p2, Point3D p3, Point3D p4, Vec3D norm)
{
        Vertices v({ p1, p2, p3, p4 });
        Indices i({ 0, 1, 2, 0, 2, 3 });
        Normals n({ norm, norm, norm, norm });
        return Mesh(v, i, n);
}

void Mesh::save(Ostream& out) const
{
        out << vertices << normals << texCoords << indices < material;
}

void Mesh::load(Istream& in)
{
        in >> vertices >> normals >> texCoords >> indices > material;
}

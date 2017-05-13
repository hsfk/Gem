#include "Package.h"
#include "Core/Loader.h"

Package::Package()
{
        Texture* empty = new Texture(Image(Image::ARGB, 1, 1, true));
        loadTexture(empty);
        
        Material def;
        def.ambient  = Vec3D(0, 1, 0);
        def.diffuse  = Vec3D(0.2, 0.2, 0.2);
        def.specular = Vec3D(0.8, 0, 0.8);
        def.specularIntensity = 2.0;
        loadMaterial(def);

        changeLock.exit();
}

Package::Package(const Package& pack)
        : Package()
{
        this->textures   = pack.textures;
        this->meshes     = pack.meshes;
        this->shaderData = pack.shaderData;
        this->materials  = pack.materials;
}

void Package::clear()
{
        ScopedLock sl(changeLock);
        for (size_t i = 0; i < textures.size(); i++)
                delete textures[i];

        textures.clear();
        materials.clear();

        meshes.clear();
        shaderData.clear();
        index.clear();
}

Texture& Package::getTexture(Index i)
{
        return *textures[i];
}

Mesh& Package::getMesh(Index i)
{
        return meshes[i];
}

ShaderData& Package::getShaderData(Index i)
{
        return shaderData[i];
}

Material& Package::getMaterial(Index i)
{
        return materials[i];
}

const Texture& Package::getTexture(Index i) const
{
        return *textures[i];
}

const Mesh& Package::getMesh(Index i) const
{
        return meshes[i];
}

const ShaderData& Package::getShaderData(Index i) const
{
        return shaderData[i];
}

const Material& Package::getMaterial(Index i) const
{
        return materials[i];
}

template <typename T, GLenum Kind, GLenum Usage>
inline void loadBuffer(Buffer<T, Kind, Usage>& buf)
{
        Engine::ext->glGenBuffers(1, &buf.handler);
        Engine::ext->glBindBuffer(buf.kind, buf.handler);
        Engine::ext->glBufferData(buf.kind, buf.byteSize(), buf.data(), buf.usage);
}

Index Package::loadMesh(Mesh mesh)
{
        ScopedLock sl(changeLock);
        meshes.push_back(mesh);
        Index i = meshes.size() - 1;
        loadBuffer(meshes[i].indices);
        loadBuffer(meshes[i].vertices);
        loadBuffer(meshes[i].normals);
        loadBuffer(meshes[i].texCoords);
        return i;
}

Index Package::loadTexture(Texture* tex)
{
        ScopedLock sl(changeLock);
        textures.push_back(tex);
        Index i = textures.size() - 1;
        tex->loadImage(tex->image);
        return i;
}

Index Package::loadShaderData(ShaderData sd)
{
        ScopedLock sl(changeLock);
        shaderData.push_back(sd);
        return shaderData.size() - 1;
}

Index Package::loadMaterial(Material mat)
{
        ScopedLock sl(changeLock);
        materials.push_back(mat);
        return materials.size() - 1;
}

void Package::addAlias(uint64_t id, Index idx)
{
        index.insert(std::make_pair(id, idx));
}

Index Package::getAlias(uint64_t id) const
{
        PackageIndex::const_iterator it = index.find(id);
        jassert(it != index.cend());
        return it->second;
}

void Package::save(Ostream& out) const
{
        ScopedLock sl(changeLock);

        out < textures.size();
        for (size_t i = 0; i < textures.size(); i++)
                out << *textures[i];

        out < meshes.size();
        for (size_t i = 0; i < meshes.size(); i++)
                out << meshes[i];

        out < shaderData.size();
        for (size_t i = 0; i < shaderData.size(); i++)
                out << shaderData[i].fragment << shaderData[i].vertex;

        out << materials;

        out < index.size();
        for (PackageIndex::const_iterator it = index.cbegin(); it != index.cend(); it++)
                out < it->first < it->second;
}

void Package::load(Istream& in)
{
        ScopedLock sl(changeLock);
        size_t size;

        in > size;
        for (size_t i = 0; i < size; i++)
        {
                Texture* tex;
                in >> (void**)&tex;
                loadTexture(tex);
        }

        in > size;
        for (size_t i = 0; i < size; i++)
        {
                Mesh m;
                in >> m;
                loadMesh(m);
        }

        shaderData.resize(in.read<size_t>());
        for (size_t i = 0; i < shaderData.size(); i++)
                in >> shaderData[i].fragment >> shaderData[i].vertex;

        in >> materials;

        size = in.read<size_t>();
        for (size_t i = 0; i < size; i++)
        {
                uint64_t key = in.read<uint64_t>();
                Index    id  = in.read<Index>();
                index.insert(std::make_pair(key, id));
        }
                
}

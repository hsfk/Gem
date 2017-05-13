#pragma once

#include "Core/Core.h"
#include "Shader/Shader.h"
#include "Light/Light.h"

typedef size_t Index;

class Package : public Serial
{
public:
        Package();
        Package(const Package& pack);
        void clear();

        Texture&          getTexture(Index i);
        Mesh&             getMesh(Index i);
        ShaderData&       getShaderData(Index i);
        Material&         getMaterial(Index i);

        const Texture&    getTexture(Index i) const;
        const Mesh&       getMesh(Index i) const;
        const ShaderData& getShaderData(Index i) const;
        const Material&   getMaterial(Index i) const;

        Index loadTexture(Texture* tex);
        Index loadMesh(Mesh mesh);
        Index loadShaderData(ShaderData sd);
        Index loadMaterial(Material mat);

        void  addAlias(uint64_t id, Index idx);
        Index getAlias(uint64_t id) const;

        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Package)

        static const Index emptyTextureIndex    = 0;
        static const Index defaultMaterialIndex = 0;

protected:
        CriticalSection    changeLock;
        Vector<Texture*>   textures;
        Vector<Mesh>       meshes;
        Vector<ShaderData> shaderData;
        Vector<Material>   materials;

        typedef std::map<uint64_t, Index> PackageIndex;
        PackageIndex index;
};
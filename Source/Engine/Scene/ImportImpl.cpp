#include "ImportImpl.h"
#include "Package.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Asset ObjImporter::importAsset(const String& obj, const String& matDir)
{
        return importAsset(obj.toStdString(), matDir.toStdString());
}

inline void convertMesh(const tinyobj::attrib_t& att, const tinyobj::mesh_t& mesh, Mesh& myMesh)
{
        std::vector<int> map(att.vertices.size() / 3, -1);
        myMesh.indices.resize(mesh.indices.size());

        for (size_t i = 0; i < mesh.indices.size(); i++)
        {
                int vIndex  = mesh.indices[i].vertex_index;
                int nIndex  = mesh.indices[i].normal_index;
                int uvIndex = mesh.indices[i].texcoord_index;
                if (map[vIndex] == -1)
                {
                        Vec3D vertex = Vec3D(att.vertices[vIndex * 3], att.vertices[vIndex * 3 + 1], att.vertices[vIndex * 3 + 2]);
                        Vec3D normal = Vec3D(att.normals[nIndex * 3], att.normals[nIndex * 3 + 1], att.normals[nIndex * 3 + 2]);
                        Vec2D uv = Vec2D(att.texcoords[uvIndex * 2], att.texcoords[uvIndex * 2 + 1]);
                        myMesh.vertices.push_back(vertex);
                        myMesh.normals.push_back(normal);
                        myMesh.texCoords.push_back(uv);
                        map[vIndex] = myMesh.vertices.size() - 1;
                }
                myMesh.indices[i] = map[vIndex];
        }

        int max = 0;
        for (size_t i = 0; i < mesh.material_ids.size(); i++)
                if (mesh.material_ids[i] > max)
                        max = mesh.material_ids[i];

        myMesh.material = max;
}

//inline Index loadTexture(const std::string& tex)
//{
//        if (tex.empty())
//                return Package::emptyTextureIndex;
//
//        asset.textures.push_back(new Texture(dir.getChildFile(String(tex))));
//        return asset.textures.size() - 1;
//}

inline Material convertMaterial(const tinyobj::material_t& mat)
{
        Material m;

        m.ambient  = Vec3D(mat.ambient[0], mat.ambient[1], mat.ambient[2]);
        m.diffuse  = Vec3D(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
        m.specular = Vec3D(mat.specular[0], mat.specular[1], mat.specular[2]);
        m.specularIntensity = mat.shininess;

        //m.ambientTex  = loadTexture(mat.ambient_texname);
        //m.diffuseTex  = loadTexture(mat.diffuse_texname);
        //m.specularTex = loadTexture(mat.specular_texname);
        //m.bumpTex     = loadTexture(mat.bump_texname);

        return m;
}

Asset ObjImporter::convert(const tinyobj::attrib_t& att
        , const std::vector<tinyobj::shape_t>& shapes
        , const std::vector<tinyobj::material_t>& materials)
{
        Asset model;
        model.meshes.resize(shapes.size());
        for (size_t i = 0; i < shapes.size(); i++)
                convertMesh(att, shapes[i].mesh, model.meshes[i]);

        for (size_t i = 0; i < materials.size(); i++)
                model.materials.push_back(convertMaterial(materials[i]));

        return model;
}

Asset ObjImporter::importAsset(const std::string& obj, const std::string& matDir)
{
        std::string message;
        std::ifstream in(obj);
        jassert(!in.fail());

        tinyobj::MaterialFileReader reader(matDir);
        DBG("\n\nLoading: " << obj);

        tinyobj::attrib_t att;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        bool res = tinyobj::LoadObj(&att, &shapes, &materials, &message, &in, &reader);

        DBG(message);
        jassert(res);

        return convert(att, shapes, materials);
}


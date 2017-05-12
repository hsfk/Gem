#pragma once

#include "Core/Core.h"
#include "Models/Model.h"
#include "Light/Light.h"

struct Asset
{
        Asset() = default;
        Asset(const Asset& other)
                : meshes(other.meshes), materials(other.materials), textures(other.textures)
        {
        }

        Asset(Asset&& other)
        {
                meshes.swap(other.meshes);
                materials.swap(other.materials);
                textures.swap(other.textures);
        }

        Vector<Mesh>     meshes;
        Vector<Material> materials;
        Vector<Texture*> textures;
};

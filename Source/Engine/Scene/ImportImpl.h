#pragma once

#include "tiny_obj_loader.h"
#include "Asset.h"

class ObjImporter
{
public:
        static Asset importAsset(const String& obj, const String& matDir);
        static Asset importAsset(const std::string& obj, const std::string& matDir);

private:
        static Asset convert(const tinyobj::attrib_t& att
                , const std::vector<tinyobj::shape_t>& shapes
                , const std::vector<tinyobj::material_t>& materials);
};
#pragma once

#include "Scene/Scene.h"

class RenderCache
{
public:
        RenderCache(size_t size = 131072);

        Mat4D getModel(const SceneNode* node, const Scene* scene);
        Mat4D getTIModel(const SceneNode* node, const Scene* scene);
        Mat4D getModel(Index node, const Scene* scene);
        Mat4D getTIModel(Index node, const Scene* scene);

private:
        struct Entry
        {
                Index  node;
                Mat4D  model;
                int    ver;
                int    parentVer;
        };

        Vector<Entry> entries;
};
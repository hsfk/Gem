#include "RenderCache.h"

RenderCache::RenderCache(size_t size)
{
        entries.resize(size);
        for (size_t i = 0; i < entries.size(); i++)
        {
                entries[i].node = -1;
                entries[i].parentVer = 0;
                entries[i].ver = 0;
        }
}

Mat4D RenderCache::getModel(const SceneNode* node, const Scene* scene)
{
        return getModel(node->getLocation(), scene);
}

Mat4D RenderCache::getTIModel(const SceneNode* node, const Scene* scene)
{
        return getTIModel(node->getLocation(), scene);
}

Mat4D RenderCache::getModel(Index node, const Scene* scene)
{
        const SceneNode* path[1000];
        int top = 0;

        const SceneNode* it = &scene->getNode(node);
        while (it->getBinding() != it->getLocation())
        {
                path[top++] = it;
                it = &scene->getNode(it->getBinding());
        }
        
        // world's zero
        if (top == 0)
                return Mat4D();

        Mat4D model;
        bool pathDirty = false;
        int  parentVer = 0;
        for (int i = top - 1; i > -1; i--)
        {
                const SceneNode* n = path[i];
                Index loc = n->getLocation();
                Entry& entry = entries[loc % entries.size()];

                if (n->isDirty() || entry.node != loc || pathDirty || entry.parentVer != parentVer)
                {
                        entry.node  = loc;
                        entry.model = model * n->getTransformMatrix();
                        entry.ver++;
                        entry.parentVer = parentVer;
                        n->setClean();
                        pathDirty = true;
                }
                parentVer = entry.ver;
                model = entry.model;
        }
        return model;

        //// no caching
        //const SceneNode& n = scene->getNode(node);
        //Mat4D bind;
        //if (n.getBinding() != n.getLocation())
        //        bind = getModel(n.getBinding(), scene);
        //return bind * n.getTransformMatrix();
}

Mat4D RenderCache::getTIModel(Index node, const Scene* scene)
{
        return glm::transpose(glm::inverse(getModel(node, scene)));
}

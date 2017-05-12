#pragma once

#include "RenderPass.h"

class RenderTech
{
public:
        virtual void render(ConstModelIterator begin, ConstModelIterator end, const Scene& scene, const Camera& cam)
        {
                return;
        }
};

template<typename Pass>
class OnePassRenderTech : public RenderTech
{
public:
        OnePassRenderTech(const OpenGLContext& context, RenderCache* cache, const ShaderData& sd)
                : cache(cache), renderPass(context)
        {
                renderPass.initialize(sd);
        }

        virtual void render(ConstModelIterator begin, ConstModelIterator end, const Scene& scene, const Camera& cam) override
        {
                renderPass(begin, end, &scene, &cam, cache);
        }

protected:
        RenderCache* cache;
        Pass         renderPass;
};

class GemRenderer : public Renderer
{
public:
        GemRenderer(const Package& pack, const OpenGLContext& context);

protected:
        virtual void renderScene(const Scene& scene, const Camera& cam) override;

private:
        RenderTech* rTechs[mrtSize];
        RenderCache cache;
};
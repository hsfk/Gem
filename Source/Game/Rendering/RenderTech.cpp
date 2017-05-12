#include "RenderTech.h"
#include "../Example/Example.h"

GemRenderer::GemRenderer(const Package& pack, const OpenGLContext& context)
{
        const ShaderData& edge   = pack.getShaderData(pack.getAlias(ridEdgeShader));
        const ShaderData& litTex = pack.getShaderData(pack.getAlias(ridForwardShader));

        rTechs[mrtNone]        = new RenderTech();
        rTechs[mrtEdges]       = new OnePassRenderTech<RenderEdgesPass>(context, &cache, edge);
        rTechs[mrtSolid]       = rTechs[mrtNone];
        rTechs[mrtLitSolid]    = rTechs[mrtNone];
        rTechs[mrtTextured]    = rTechs[mrtNone];                          
        rTechs[mrtLitTextured] = new OnePassRenderTech<ForwardRenderPass>(context, &cache, litTex);
}

void GemRenderer::renderScene(const Scene& scene, const Camera& cam)
{
        const Vector<Index>& models = scene.getModels();
        ConstModelIterator it = models.cbegin();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //OpenGLHelpers::clear(Colours::darkblue);
        while (it < models.cend())
        {
                enum ModelRenderType type  = scene.getModel(it).renderType;
                ConstModelIterator   begin = it;
                while (it < models.cend() && scene.getModel(it).renderType == type)
                        it++;

                rTechs[type]->render(begin, it, scene, cam);
        }
}

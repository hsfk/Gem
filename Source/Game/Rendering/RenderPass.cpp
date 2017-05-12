#include "RenderPass.h"

RenderPass::RenderPass(const OpenGLContext& context)
        : shader(context)
{
}

void RenderPass::initialize(const ShaderData& sd)
{
        shader.initialize(sd);
        
        a_Pos.initialize(shader,          "a_Pos");
        a_Norm.initialize(shader,         "a_Norm");
        a_UV.initialize(shader,           "a_UV");
        
        u_VP.initialize(shader,           "u_VP");
        u_Model.initialize(shader,        "u_Model");
        u_TIModel.initialize(shader,      "u_TIModel");
        
        u_EyePos.initialize(shader,       "u_EyePos");
        u_Material.initialize(shader,     "u_Material");
        u_AmbientLight.initialize(shader, "u_AmbientLight");
        u_PointLights.initialize(shader,  "u_PointLights");
        u_SpotLights.initialize(shader,   "u_SpotLights");
        u_DirLights.initialize(shader,    "u_DirLights");
}

void RenderPass::attach()
{
        shader.use();
}

void RenderGeometryPass::setAttribs() const
{
        a_Pos   = mesh->vertices;
        a_Index = mesh->indices;
}

void RenderEdgesPass::setModelUniforms() const
{
        u_Model = cache->getModel(model, scene);
}

void RenderEdgesPass::setGlobalUniforms() const
{
        u_VP = eye->getVP();
}

void RenderLightPass::setGlobalUniforms() const
{
        u_EyePos       = eye->getPos();
        u_AmbientLight = scene->getAmbientLight();

        const Vector<Index>& dLights = scene->getDirLights();
        GLint count = glm::min(MAX_DIR_LIGHTS, GLint(dLights.size()));
        u_DirLights.count = count;
        for (int i = 0; i < count; i++)
                u_DirLights.sources[i] = scene->getDirLight(i);

        const Vector<Index>& pLights = scene->getPointLights();
        count = glm::min(MAX_POINT_LIGHTS, GLint(pLights.size()));
        u_PointLights.count = count;
        for (GLint i = 0; i < count; i++)
        {
                PointLight light = scene->getPointLight(i);
                light.setPos(Vec3D(cache->getModel(pLights[i], scene) * Vec4D(light.getPos(), 1.0)));
                u_PointLights.sources[i] = light;
        }

        const Vector<Index>& sLights = scene->getSpotLights();
        count = glm::min(MAX_SPOT_LIGHTS, GLint(sLights.size()));
        u_SpotLights.count = count;
        for (GLint i = 0; i < count; i++)
        {
                SpotLight light = scene->getSpotLight(i);
                Mat4D mmodel = cache->getModel(sLights[i], scene);
                light.setPos(Vec3D(mmodel * Vec4D(light.getPos(), 1.0)));
                u_SpotLights.sources[i] = light;
        }
}

void ForwardRenderPass::setAttribs() const
{
        a_Pos   = mesh->vertices;
        a_Norm  = mesh->normals;
        a_UV    = mesh->texCoords;
        a_Index = mesh->indices;
}

void ForwardRenderPass::setModelUniforms() const
{
        u_Model    = cache->getModel(model, scene);
        u_TIModel  = cache->getTIModel(model, scene);
        u_Material = pack->getMaterial(mesh->material);
}

void ForwardRenderPass::setGlobalUniforms() const
{
        RenderLightPass::setGlobalUniforms();
        u_VP = eye->getVP();
}

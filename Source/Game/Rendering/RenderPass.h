#pragma once

#include "Scene/Scene.h"
#include "Shader/Shader.h"
#include "Shader/ULight.h"
#include "Shader/Attribute.h"
#include "RenderCache.h"

class RenderPass
{
public:
        RenderPass(const OpenGLContext& context);
        void initialize(const ShaderData& sd);

        inline void operator()(
                ConstModelIterator   begin
                , ConstModelIterator end
                , const Scene*       scene
                , const Camera*      eye
                , RenderCache*       cache)
        {
                this->scene = scene;
                this->cache = cache;
                this->eye   = eye;
                pack        = &scene->getPackage();

                attach();
                setGlobalUniforms();
                for (; begin < end; begin++)
                {
                        model = &scene->getModel(begin);
                        mesh  = &pack->getMesh(model->mesh);
                        setAttribs();   
                        setModelUniforms();

                        GLenum mode = GL_TRIANGLES;
                        if (model->renderType == mrtEdges)
                                mode = GL_LINE_LOOP;

                        glDrawElements(mode, mesh->indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
                }
                deattach();
        }

protected:
        virtual void attach();
        virtual void deattach() {}

        virtual void setAttribs() const {}
        virtual void setModelUniforms() const {}
        // set model independent uniforms
        virtual void setGlobalUniforms() const {}

        const Scene*         scene;
        const Mesh*          mesh;
        const Package*       pack;
        const Model*         model;
        const Camera*        eye;
        RenderCache*         cache;
        
        Attribute<Vertices>      a_Pos;
        Attribute<Normals>       a_Norm;
        Attribute<TextureCoords> a_UV;
        Attribute<Indices>       a_Index;
        
        Uniform<Mat4D>           u_VP;
        Uniform<Mat4D>           u_Model;
        Uniform<Mat3D>           u_TIModel;
        
        Uniform<Vec3D>           u_EyePos;
        UMaterial                u_Material;
        ULightBase               u_AmbientLight;
        UPointLightSources       u_PointLights;
        USpotLightSources        u_SpotLights;
        UDirLightSources         u_DirLights;
        
private:
        Shader shader;
};

class RenderGeometryPass : public RenderPass
{
public:
        using RenderPass::RenderPass;

protected:
        virtual void setAttribs() const override;
};

class RenderEdgesPass : public RenderGeometryPass
{
public:
        using RenderGeometryPass::RenderGeometryPass;

protected:
        virtual void setModelUniforms() const override;
        virtual void setGlobalUniforms() const override;
};

class RenderLightPass : public RenderPass
{
public:
        using RenderPass::RenderPass;

protected:
        virtual void setGlobalUniforms() const override;
};

class ForwardRenderPass : public RenderLightPass
{
public:
        using RenderLightPass::RenderLightPass;

protected:
        virtual void setAttribs() const override;
        virtual void setModelUniforms() const override;
        virtual void setGlobalUniforms() const override;
};

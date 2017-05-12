#include "Engine.h"

OpenGLExtensionFunctions* Engine::ext = nullptr;
OpenGLContext*            Engine::context = nullptr;

void Engine::init(juce::OpenGLExtensionFunctions* e, OpenGLContext* c)
{
        ext = e;
        context = c;

        //SceneManager::createScene();
        //// core
        //SerialTypeInfo::regType<Camera>();
        //SerialTypeInfo::regType<Placement>();
        //SerialTypeInfo::regType<Transformable>();
        //SerialTypeInfo::regType<Vertices>();
        //SerialTypeInfo::regType<Indices>();
        //SerialTypeInfo::regType<Normals>();
        //SerialTypeInfo::regType<TextureCoords>();
        //SerialTypeInfo::regType<Texture>();
        //SerialTypeInfo::regType<Mesh>();
        //// model
        //SerialTypeInfo::regType<Model>();
        //// light
        //SerialTypeInfo::regType<SpotLight>();
        //SerialTypeInfo::regType<PointLight>();
        //// world
        //SerialTypeInfo::regType<Entity>();
        //SerialTypeInfo::regType<World>();
        //SerialTypeInfo::regType<Entity>();
        //SerialTypeInfo::regType<Vector<SceneObject>>();
        //// entities
        //SerialTypeInfo::regType<Actor>();
        //SerialTypeInfo::regType<LightSource>();
        //// shader
        //SerialTypeInfo::regType<Shader>(new ShaderConstructor<Shader>(context));
        //// render
        //SerialTypeInfo::regType<SceneBase>();
        //SerialTypeInfo::regType<SceneBase::PointLights>();
        //SerialTypeInfo::regType<SceneBase::SpotLights>();
        //SerialTypeInfo::regType<SceneBase::DirLights>();
        //SerialTypeInfo::regType<SceneBase::Materials>();
        //SerialTypeInfo::regType<SceneBase::Meshes>();
        //SerialTypeInfo::regType<Scene>(new SceneConstructor());

        //SerialTypeInfo::regType<RenderTech>();
        //SerialTypeInfo::regType<GeometryRenderTech>();
        //SerialTypeInfo::regType<ForwardRenderTech>();
        //SerialTypeInfo::regType<DefferedRenderTech>();
        //// level
        //SerialTypeInfo::regType<Level>();
}
#include "Engine.h"

OpenGLExtensionFunctions* Engine::ext = nullptr;
OpenGLContext*            Engine::context = nullptr;

void Engine::init(juce::OpenGLExtensionFunctions* e, OpenGLContext* c)
{
        ext = e;
        context = c;

        // core
        SerialTypeInfo::regType<SceneObject>();
        SerialTypeInfo::regType<SceneNode>();
        SerialTypeInfo::regType<Camera>();
        SerialTypeInfo::regType<Placement>();
        SerialTypeInfo::regType<Transformable>();
        SerialTypeInfo::regType<Vertices>();
        SerialTypeInfo::regType<Indices>();
        SerialTypeInfo::regType<Normals>();
        SerialTypeInfo::regType<TextureCoords>();
        SerialTypeInfo::regType<Texture>();
        SerialTypeInfo::regType<Mesh>();
        // model
        SerialTypeInfo::regType<Model>();
        // light
        SerialTypeInfo::regType<DirLight>();
        SerialTypeInfo::regType<SpotLight>();
        SerialTypeInfo::regType<PointLight>();
        // world
        SerialTypeInfo::regType<Entity>();
        SerialTypeInfo::regType<World>();
        SerialTypeInfo::regType<Entity>();
        SerialTypeInfo::regType<Actor>();
        // scene
        SerialTypeInfo::regType<Package>();     
        SerialTypeInfo::regType<Vector<Index>>();
        SerialTypeInfo::regType<Vector<Material>>();
        SerialTypeInfo::regType<Scene>();
        // level
        SerialTypeInfo::regType<Level>();
        SerialTypeInfo::regType<Renderer>();
}
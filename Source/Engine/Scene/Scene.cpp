#include "Scene.h"

Scene::Scene()
{
        // world zero
        nodes.push_back(loadObject(new SceneNode()));
}

Scene::Scene(const Package& pack)
        : pack(pack)
{
}

Package& Scene::getPackage()
{
        return pack;
}

SceneObject& Scene::getObject(Index i)
{
        return *objects[i];
}

SceneNode& Scene::getNode(Index i)
{
        return reinterpret_cast<SceneNode&>(getObject(nodes[i]));
}

Model& Scene::getModel(Index i)
{
        return reinterpret_cast<Model&>(getNode(models[i]));
}

const Package& Scene::getPackage() const
{
        return pack;
}

const SceneObject& Scene::getObject(Index i) const
{
        return *objects[i];
}

const SceneNode& Scene::getNode(Index i) const
{
        return reinterpret_cast<const SceneNode&>(getObject(nodes[i]));
}

const Model& Scene::getModel(Index i) const
{
        return reinterpret_cast<const Model&>(getNode(models[i]));
}

const Model& Scene::getModel(const ConstModelIterator& it) const
{
        return reinterpret_cast<const Model&>(getNode(*it));
}

const Vector<Index>& Scene::getModels() const
{
        return models;
}

const LightBase& Scene::getAmbientLight() const
{
        return ambientLight;
}

const DirLight& Scene::getDirLight(Index i) const
{
        return reinterpret_cast<const DirLight&>(getNode(dirLights[i]));
}

const PointLight& Scene::getPointLight(Index i) const
{
        return reinterpret_cast<const PointLight&>(getNode(pointLights[i]));
}

const SpotLight& Scene::getSpotLight(Index i) const
{
        return reinterpret_cast<const SpotLight&>(getNode(spotLights[i]));
}

const Vector<Index>& Scene::getPointLights() const
{
        return pointLights;
}

const Vector<Index>& Scene::getDirLights() const
{
        return dirLights;
}

const Vector<Index>& Scene::getSpotLights() const
{
        return spotLights;
}

void Scene::setAmbientLight(const LightBase& ambient)
{
        ambientLight = ambient;
}

void Scene::lock()
{
        changeLock.enter();
}

void Scene::unlock()
{
        changeLock.exit();
}

void Scene::save(Ostream& out) const
{
        jassertfalse;
}

void Scene::load(Istream& in)
{
        jassertfalse;
}

Index Scene::loadObject(SceneObject* obj)
{
        objects.push_back(obj);
        return objects.size() - 1;
}

Index Scene::loadNode(SceneNode* node)
{
        Index n = nodes.size();
        nodes.push_back(loadObject(node));
        node->setLocation(n);
        return n;
}

Index Scene::load(Vector<Index>& vec, SceneNode* node)
{
        vec.push_back(loadNode(node));
        return vec.size() - 1;
}

Index Scene::loadModel(Model* model)
{
        return load(models, model);
}

Index Scene::loadAsset(Asset& asset, Index node)
{
        for (size_t i = 0; i < asset.meshes.size(); i++)
        {
                Mesh& mesh = asset.meshes[i];
                if (!asset.materials.size())
                        mesh.material = Package::defaultMaterialIndex;
                else
                        mesh.material = pack.loadMaterial(asset.materials[mesh.material]);

                Index  meshId = pack.loadMesh(mesh);
                Model* model  = new Model(meshId);
                model->renderType = mrtLitTextured;
                loadModel(model);
                model->bind(node);
        }
        return node;
}

Index Scene::loadPointLight(PointLight* light)
{
        return load(pointLights, light);
}

Index Scene::loadSpotLight(SpotLight* light)
{
        return load(spotLights, light);
}

Index Scene::addNode(Index obj)
{
        nodes.push_back(obj);
        return nodes.size() - 1;
}

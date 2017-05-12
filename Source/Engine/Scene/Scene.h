#pragma once

#include "Package.h"
#include "Models/Model.h"
#include "Light/Light.h"
#include "Asset.h"

typedef Vector<Index>::const_iterator ConstModelIterator;

class Scene : public Serial
{
public:
        Scene();
        Scene(const Package& pack);

        Package&             getPackage();
        SceneObject&         getObject(Index i);
        SceneNode&           getNode(Index i);
        Model&               getModel(Index i);
                             
        const Package&       getPackage() const;
        const SceneObject&   getObject(Index i) const;
        const SceneNode&     getNode(Index i) const;
        const Model&         getModel(Index i) const;
        const Model&         getModel(const ConstModelIterator& it) const;
        const Vector<Index>& getModels() const;

        const LightBase&     getAmbientLight() const;
        const DirLight&      getDirLight(Index i) const;
        const PointLight&    getPointLight(Index i) const;
        const SpotLight&     getSpotLight(Index i) const;
        const Vector<Index>& getPointLights() const;
        const Vector<Index>& getDirLights() const;
        const Vector<Index>& getSpotLights() const;

        void                 setAmbientLight(const LightBase& ambient);

        Index loadObject(SceneObject* obj);
        Index loadNode(SceneNode* node);
        Index loadModel(Model* model);
        Index loadAsset(Asset& asset, Index node = worldZeroIndex);
        Index loadPointLight(PointLight* light);
        Index loadSpotLight(SpotLight* light);

        Index addNode(Index obj);

        void lock();
        void unlock();

        DECLARE_SERIAL(Scene)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

        static const Index worldZeroIndex = 0;

private:
        Index load(Vector<Index>& vec, SceneNode* node);

        CriticalSection changeLock; // insert/delete

        Package pack;

        Vector<SceneObject*> objects;
        Vector<Index>        nodes;
        Vector<Index>        models;

        LightBase            ambientLight;
        Vector<Index>        pointLights;
        Vector<Index>        dirLights;
        Vector<Index>        spotLights;
};

class Renderer : public Serial
{
public:
        void render(Scene& scene, const Camera& cam)
        {
                Camera copy(cam);
                scene.lock();
                renderScene(scene, copy);
                scene.unlock();
        }

        virtual void save(Ostream& out) const override {}
        virtual void load(Istream& in) override {}
        DECLARE_SERIAL(Renderer)

protected:
        virtual void renderScene(const Scene& scene, const Camera& cam)
        {
                return;
        }
};
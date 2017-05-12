#pragma once

#include "Level/Level.h"
#include "Controller.h"

class GameManager;

using GMCallBack = std::function<void(void)>;

class MainComponentBase : public OpenGLAppComponent
{
public:
        MainComponentBase(GMCallBack onLoad);
        virtual void initialise() override;
        virtual void shutdown() override;
        
private:
        GMCallBack onLoad;
};

class MainComponent : public MainComponentBase
{
public:
        MainComponent(GMCallBack onLoad);
        virtual void render() override;
        virtual void paint(Graphics& g) override;

        void initialize(Level* lvl);
private:
        Level* lvl;
        bool   initialized;

        uint64_t renderTimeMs;
};

class GameManager
{
public:
        GameManager();
        MainComponent* getComponent();
        void shutdown();
private:
        Level* lvl;
        Config cfg;

        Controller controller;
        MainComponent comp;

        void initialize();
};

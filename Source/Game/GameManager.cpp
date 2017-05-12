#include "GameManager.h"
#include "Example/Example.h"

MainComponentBase::MainComponentBase(GMCallBack onLoad)
        : onLoad(onLoad)
{
}

void MainComponentBase::initialise()
{
        onLoad();
}

void MainComponentBase::shutdown()
{
}

MainComponent::MainComponent(GMCallBack onLoad)
        : MainComponentBase(onLoad), initialized(false)
{
}

void MainComponent::render()
{
        if (!initialized)
                return;
        uint64_t t = Time::currentTimeMillis();
        lvl->render();
        renderTimeMs = Time::currentTimeMillis() - t;
        repaint();
}

void MainComponent::paint(Graphics& g)
{
        String text = "Render time ms: " + String(renderTimeMs);
        g.setColour(Colours::green);
        g.drawText(text, 10, 10, 200, 40, Justification::topLeft);
}

void MainComponent::initialize(Level* lvl)
{
        this->lvl = lvl;
        initialized = true;
}

GameManager::GameManager()
        : comp(std::bind(&GameManager::initialize, this))
{
        comp.setSize(cfg.screenWidth, cfg.screenHeight);
}

void GameManager::initialize()
{
        Engine::init(&comp.openGLContext.extensions, &comp.openGLContext);

        lvl = new ExampleLevel();
        lvl->initialize();

        comp.initialize(lvl);
        controller.initialize(comp, lvl);
}

void GameManager::shutdown()
{
        controller.shutdown();
        comp.shutdownOpenGL();
}

MainComponent* GameManager::getComponent()
{
        return &comp;
}

#include "App.h"

MainWindow::MainWindow(String name) 
        : DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
{
        setUsingNativeTitleBar(true);
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
        setVisible(true);
}

void MainWindow::closeButtonPressed()
{
        JUCEApplication::getInstance()->systemRequestedQuit();
}

GemApplication::GemApplication()
{
}

const String GemApplication::getApplicationName()
{
        return ProjectInfo::projectName;
}

const String GemApplication::getApplicationVersion()
{
        return ProjectInfo::versionString;
}

bool GemApplication::moreThanOneInstanceAllowed()
{
        return false;
}

void GemApplication::initialise(const String& commandLine)
{
        mainWindow = new MainWindow(getApplicationName());
        mainWindow->setContentOwned(gm.getComponent(), true);
}

void GemApplication::shutdown()
{
        mainWindow = nullptr;
}

void GemApplication::systemRequestedQuit()
{
        gm.shutdown();
        quit();
}

void GemApplication::anotherInstanceStarted(const String& commandLine)
{
}

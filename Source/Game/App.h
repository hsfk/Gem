#pragma once


#include <JuceHeader.h>

#include "GameManager.h"

using namespace juce;

class MainWindow : public DocumentWindow
{
public:
        MainWindow(String name);
        void closeButtonPressed() override;

private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

class GemApplication : public JUCEApplication
{
public:

        GemApplication();
        const String getApplicationName() override;
        const String getApplicationVersion() override;
        bool moreThanOneInstanceAllowed() override;
        void initialise(const String& commandLine) override;
        void shutdown() override;
        void systemRequestedQuit() override;
        void anotherInstanceStarted(const String& commandLine) override;

private:
        GameManager gm;

        ScopedPointer<MainWindow> mainWindow;
};

#pragma once

#include "Level/Level.h"
#include <map>

class Controller : private KeyListener, private Timer, private MouseListener
{
public:
        void initialize(OpenGLAppComponent& comp, Level* lvl);
        void shutdown();
private:
        Level* lvl;

        std::map<int, KeyPress> keys;
        Point<int> mousePrev;

        virtual bool pressed(int code) const;
        virtual bool keyPressed(const KeyPress& key, Component* origin) override;
        virtual void mouseDown(const MouseEvent& event) override;
        virtual void mouseDrag(const MouseEvent& event) override;
        virtual void timerCallback() override;
};

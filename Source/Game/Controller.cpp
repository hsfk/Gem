#include "Controller.h"

void Controller::initialize(OpenGLAppComponent& comp, Level* lvl)
{
        this->lvl = lvl;
        const MessageManagerLock lock;
        comp.setWantsKeyboardFocus(true);
        comp.addKeyListener(this);
        comp.addMouseListener(this, true);
        startTimer(10);
}

void Controller::shutdown()
{
        stopTimer();
}

bool Controller::pressed(int code) const
{
        std::map<int, KeyPress>::const_iterator it = keys.find(code);
        return it == keys.end() ? 0 : it->second.isCurrentlyDown();
}

bool Controller::keyPressed(const KeyPress& key, Component* origin)
{
        keys[key.getKeyCode()] = key;
        return false;
}

void Controller::mouseDown(const MouseEvent& event)
{
        mousePrev = event.getPosition();
}

void Controller::mouseDrag(const MouseEvent& event)
{
        Point<int> delta = mousePrev - event.getPosition();
        Point<GLfloat> d(-delta.x, -delta.y);
        d *= 0.001f;
        lvl->getPlayer()->rotate(Angle3D(d.x, d.y, 0));
        mousePrev = event.getPosition();
}

void Controller::timerCallback()
{
        
        Actor* player = lvl->getPlayer();
        Camera::Axes a = player->cam.getAxes();
        const GLfloat scale = 0.04f;

        if (pressed('W'))
                player->move(-a.dir * scale);
        if (pressed('S'))
                player->move(a.dir * scale);
        if (pressed('A'))
                player->move(-a.right * scale);
        if (pressed('D'))
                player->move(a.right * scale);
        if (pressed(' '))
                player->move(a.up * scale);
        if (pressed('C'))
                player->move(-a.up * scale);

        lvl->invalidate();
}

#pragma once

#include "World/Actor.h"

class Level : public Serial
{
public:
        Level();
        virtual void initialize();
        void         invalidate();
        void         render();

        Actor* getPlayer();

        DECLARE_SERIAL(Level)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

protected:
        Scene     scene;
        World     world;
        Renderer* renderer;
        Actor*    player;
};

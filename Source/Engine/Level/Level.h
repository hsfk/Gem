#pragma once

#include "World/Actor.h"

class Level : public Serial
{
public:
        Level();
        void         clear();
        virtual void initialize();
        void         invalidate();
        void         render();

        Actor& getPlayer();
        void   setPlayer(Actor* player);

        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Level)

protected:
        Scene     scene;
        World     world;
        Renderer* renderer;
        Index     player;
};

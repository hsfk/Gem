#pragma once

#include "Serial.h"
#include "Types.h"

typedef size_t Index;

class SceneObject : public Serial
{
public:
        virtual void save(Ostream& out) const override
        {
                return;
        }

        virtual void load(Istream& in) override
        {
                return;
        }

        DECLARE_SERIAL(SceneObject)
};

class SceneNode : public SceneObject
{
public:
        SceneNode();

        virtual Mat4D getTransformMatrix() const;

        Index getBinding() const;
        void  bind(Index i);
        void  bind(const SceneNode& other);
        Index getLocation() const;
        void  setLocation(Index loc);
              
        bool  isDirty() const;
        void  setDirty() const;
        void  setClean() const;

        virtual void  save(Ostream& out) const override;
        virtual void  load(Istream& in) override;


        DECLARE_SERIAL(SceneNode)

protected:
        Index location;
        Index binding; // the other scene node

private:
        mutable bool dirty; // flag for caching transform matrices
};
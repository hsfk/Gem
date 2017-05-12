#pragma once

#include "Level/Level.h"
#include "../Resource.h"

enum ResID
{
        ridRectMesh,
        ridTriangleMesh,
        ridCubeMesh,
        ridCubeFaceMesh0,
        ridCubeFaceMesh1,
        ridCubeFaceMesh2,
        ridCubeFaceMesh3,
        ridCubeFaceMesh4,
        ridCubeFaceMesh5,

        ridEdgeShader,
        ridForwardShader,
};

class ExampleResources : public Resources
{
public:
        ExampleResources();
        void loadAll(Scene& scene);

private:
        void loadMeshes(Scene& scene);
        void loadShaders(Scene& scene);
};

class ExampleLevel : public Level
{
public:
        virtual void initialize() override;

protected:

        ExampleResources res;
        Config cfg;
};
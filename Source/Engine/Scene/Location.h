#pragma once

#include "Core/SceneObject.h"

struct SceneObjectLocation
{
        Index objectIndex;
};

struct SceneNodeLocation : SceneObjectLocation
{
        Index nodeIndex;
};

struct VectorLocation : SceneNodeLocation
{
        Index vecIndex;
};
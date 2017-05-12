#pragma once

#include <glm/glm.hpp>

typedef glm::vec3   Vec3D;
typedef Vec3D       Point3D;
typedef Vec3D       Angle3D;
typedef glm::mat4x4 Mat4D;
typedef glm::mat3x3 Mat3D;
typedef glm::vec2   Vec2D;
typedef Vec2D       Point2D;
typedef glm::vec4   Vec4D;
typedef Vec4D       Point4D;

#include <JuceHeader.h>
#include "Vector.h"

template<typename T>
using SharedPtr = std::shared_ptr<T>;
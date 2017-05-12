#ifndef COMMON_H
#define COMMON_H

#include "light.h"

#ifndef FRAGMENT_SHADER
attribute vec3            a_Pos;
attribute vec3            a_Norm;
attribute vec2            a_UV;
#endif

varying vec3              v_Pos;
varying vec3              v_Norm;
varying vec2              v_UV;

uniform mat4              u_VP;
uniform mat4              u_Model;
uniform mat3              u_TIModel;

uniform vec3              u_EyePos;
uniform LightBase         u_AmbientLight;
uniform PointLightSources u_PointLights;
uniform SpotLightSources  u_SpotLights;
uniform DirLightSources   u_DirLights;
uniform Material          u_Material;

vec3                      g_Norm;
vec3                      g_ViewDir;
vec3                      g_FragPos;
MaterialInfo              g_Material;

#endif

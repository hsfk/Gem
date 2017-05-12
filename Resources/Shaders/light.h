#ifndef LIGHT_H
#define LIGHT_H

#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS  16
#define MAX_DIR_LIGHTS   16

struct LightBase
{
        vec3 col;
        float ambient;
        float diffuse;
        float specular;
};

struct DirLight
{
	LightBase base;
	vec3 dir;
};

struct PointLight
{
        LightBase base;

        struct
        {
                float cst;
                float linear;
                float exp;
        } att;

        vec3 pos;
};

struct SpotLight
{
        PointLight base;
        vec3 dir;
        float cutOff;
        float outerCutOff;
};

struct DirLightSources
{
	int count;
	DirLight sources[MAX_DIR_LIGHTS];
};

struct SpotLightSources
{
        int count;
        SpotLight sources[MAX_SPOT_LIGHTS];
};

struct PointLightSources
{
        int count;
        PointLight sources[MAX_POINT_LIGHTS];
};

struct MaterialInfo
{
        vec3  ambient;
        vec3  diffuse;
        vec3  specular;
        float specularIntensity;
};

struct Material
{
	vec3  ambient;
	vec3  diffuse;
	vec3  specular;
	float specularIntensity;

	sampler2D ambientTex;
	sampler2D diffuseTex;
	sampler2D specularTex;
	sampler2D bumpTex;
};

#endif
#pragma once

#include "Uniform.h"
#include "Light/Light.h"

#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS  16
#define MAX_DIR_LIGHTS   16

struct ULightBase
{
        void initialize(const Shader& shader, const String& baseName);
        const ULightBase& operator=(const LightBase& light) const;

        Uniform<Vec3D>   col;
        Uniform<GLfloat> ambient;
        Uniform<GLfloat> diffuse;
        Uniform<GLfloat> specular;
};

struct UDirLight
{
        void initialize(const Shader& shader, const String& baseName);
        const UDirLight& operator=(const DirLight& light) const;

        ULightBase base;
        Uniform<Vec3D> dir;
};

struct UPointLight
{
        void initialize(const Shader& shader, const String& baseName);
        const UPointLight& operator=(const PointLight& light) const;

        ULightBase base;

        struct
        {
                Uniform<GLfloat> cst;
                Uniform<GLfloat> linear;
                Uniform<GLfloat> exp;
        } att;

        Uniform<Vec3D> pos;
};

struct USpotLight
{
        void initialize(const Shader& shader, const String& baseName);

        const USpotLight& operator=(const SpotLight& light) const;

        UPointLight base;
        Uniform<Vec3D> dir;
        Uniform<GLfloat> cutOff;
        Uniform<GLfloat> outerCutOff;
};

template <typename LightLoc, int MaxCount>
struct ULightSources
{
        void initialize(const Shader& shader, const String& baseName)
        {
                count.initialize(shader, baseName + ".count");
                for (int i = 0; i < MAX_POINT_LIGHTS; i++)
                        sources[i].initialize(shader, baseName + ".sources[" + String(i) + "]");
        }

        Uniform<GLint> count;
        LightLoc sources[MaxCount];
};

typedef ULightSources<USpotLight, MAX_SPOT_LIGHTS>   USpotLightSources;
typedef ULightSources<UPointLight, MAX_POINT_LIGHTS> UPointLightSources;
typedef ULightSources<UDirLight, MAX_DIR_LIGHTS>     UDirLightSources;

struct UMaterial
{
        void initialize(const Shader& shader, const String& baseName);
        const UMaterial& operator=(const Material& mat) const;

        Uniform<Vec3D>     ambient;
        Uniform<Vec3D>     diffuse;
        Uniform<Vec3D>     specular;
        Uniform<GLfloat>   specularIntensity;
        
        Uniform<Sampler2D> ambientTex;
        Uniform<Sampler2D> diffuseTex;
        Uniform<Sampler2D> specularTex;
        Uniform<Sampler2D> bumpTex;
};

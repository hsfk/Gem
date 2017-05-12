#pragma once

#include "Core/Buffer.h"
#include "Core/Transformable.h"

struct LightBase
{
        Vec3D   col;
        GLfloat ambient;
        GLfloat diffuse;
        GLfloat specular;

        LightBase();
        LightBase(Vec3D col, GLfloat ambient, GLfloat diffuse, GLfloat specular);
        LightBase(const LightBase& l);

        static LightBase defaultLight();
};

class DirLight : public SceneNode, public LightBase
{
public:
        DirLight() = default;
        DirLight(const Vec3D& dir);
        DirLight(const DirLight& d);

        Vec3D dir;
};

struct PointLight : Placement, LightBase
{
        PointLight() = default;
        PointLight(const Point3D& pos);
        PointLight(const PointLight& p);

        struct
        {
                GLfloat cst;
                GLfloat linear;
                GLfloat exp;
        } att;

        DECLARE_SERIAL(PointLight)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

        static PointLight blue(const Point3D& pos);
        static PointLight white(const Point3D& pos);
        static PointLight red(const Point3D& pos);
        static PointLight yellow(const Point3D& pos);
        static PointLight aqua(const Point3D& pos);
};

struct SpotLight : PointLight
{
        SpotLight();
        SpotLight(const Point3D& pos, const Point3D& target);
        SpotLight(const SpotLight& s);
        SpotLight(const PointLight& p);
        SpotLight(const PointLight& p, GLfloat cutOff, GLfloat outerCutOff);

        DECLARE_SERIAL(SpotLight)
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;

        Point3D target;
        GLfloat cutOff;
        GLfloat outerCutOff;
};

struct Material
{
        Material();

        Vec3D   ambient;
        Vec3D   diffuse;
        Vec3D   specular;
        GLfloat specularIntensity;

        Index   ambientTex;
        Index   diffuseTex;
        Index   specularTex;
        Index   bumpTex;
};

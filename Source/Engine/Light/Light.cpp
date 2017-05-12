#include "Light.h"
#include "Core/Common.h"
#include "Scene/Package.h" // emptyTexture

LightBase::LightBase()
        : ambient(0.0), diffuse(0.0), specular(0.0), col(Vec3D(0.0, 0.0, 0.0))
{
}

LightBase::LightBase(Vec3D col, GLfloat ambient, GLfloat diffuse, GLfloat specular)
        : col(col), ambient(ambient), diffuse(diffuse), specular(specular)
{
}

LightBase::LightBase(const LightBase& l)
        : ambient(l.ambient), diffuse(l.diffuse), specular(l.specular), col(l.col)
{
}

LightBase LightBase::defaultLight()
{
        return LightBase(Vec3D(1, 1, 1), 1, 0, 0);
}

DirLight::DirLight(const Vec3D& dir)
        : dir(dir)
{
}

DirLight::DirLight(const DirLight& d)
        : LightBase(d), dir(d.dir)
{
}

PointLight::PointLight(const Point3D& pos)
        : Placement(pos)
{
        att.cst = 0.0;
        att.exp = 0.0;
        att.linear = 0.0;
}

PointLight::PointLight(const PointLight& p)
        : LightBase(p), Placement(p)
{
        att.cst = p.att.cst;
        att.exp = p.att.exp;
        att.linear = p.att.linear;
}

void PointLight::save(Ostream& out) const
{
        Placement::save(out);
        out < att < static_cast<const LightBase&>(*this);
}

void PointLight::load(Istream& in)
{
        Placement::load(in);
        in > att > static_cast<LightBase&>(*this);
}

PointLight PointLight::blue(const Point3D& pos)
{
        PointLight p(pos);
        p.col = Vec3D(0, 0.3, 1);
        p.att.linear = 0.8;
        p.specular = 3;
        p.diffuse = 0.4;
        return p;
}

PointLight PointLight::white(const Point3D& pos)
{
        PointLight p(pos);
        p.col = Vec3D(1, 1, 1);
        p.att.linear = 0.8;
        p.specular = 5;
        p.diffuse = 0.6;
        return p;
}

PointLight PointLight::red(const Point3D& pos)
{
        PointLight p(pos);
        p.col = Vec3D(1, 0.3, 0.3);
        p.att.linear = 0.8;
        p.specular = 4;
        p.diffuse = 2;
        return p;
}

PointLight PointLight::yellow(const Point3D& pos)
{
        PointLight p(pos);
        p.col = Vec3D(1, 1, 0);
        p.att.linear = 0.8;
        p.att.exp = 0.6;
        p.specular = 4;
        p.diffuse = 2;
        return p;
}

PointLight PointLight::aqua(const Point3D& pos)
{
        PointLight p(pos);
        p.col = Vec3D(0, 1, 1);
        p.att.linear = 0.4;
        p.att.exp = 0.6;
        p.specular = 14;
        p.diffuse = 2;
        return p;
}

SpotLight::SpotLight()
        : cutOff(0.0), outerCutOff(0.0)
{
}

SpotLight::SpotLight(const Point3D& pos, const Point3D& target)
        : PointLight(pos), target(target), cutOff(0.0), outerCutOff(0.0)
{
}

SpotLight::SpotLight(const SpotLight& s)
        : PointLight(s), target(s.target), cutOff(s.cutOff), outerCutOff(s.outerCutOff)
{
}

SpotLight::SpotLight(const PointLight& p)
        : PointLight(p)
{
}

SpotLight::SpotLight(const PointLight& p, GLfloat cutOff, GLfloat outerCutOff)
        : PointLight(p), cutOff(cutOff), outerCutOff(outerCutOff)
{
}

void SpotLight::save(Ostream& out) const
{
        PointLight::save(out);
        out < target < cutOff < outerCutOff;
}

void SpotLight::load(Istream& in)
{
        PointLight::load(in);
        in > target > cutOff > outerCutOff;
}

Material::Material()
        : ambient(Vec3D()), diffuse(Vec3D()), specular(Vec3D()), specularIntensity(0),
        ambientTex(Package::emptyTextureIndex),
        diffuseTex(Package::emptyTextureIndex),
        specularTex(Package::emptyTextureIndex),
        bumpTex(Package::emptyTextureIndex)
{
}

#include "ULight.h"

void ULightBase::initialize(const Shader& shader, const String& baseName)
{
        col.initialize(shader, baseName + ".col");
        ambient.initialize(shader, baseName + ".ambient");
        diffuse.initialize(shader, baseName + ".diffuse");
        specular.initialize(shader, baseName + ".specular");
}

const ULightBase& ULightBase::operator=(const LightBase& light) const
{
        col = light.col;
        ambient = light.ambient;
        diffuse = light.diffuse;
        specular = light.specular;
        return *this;
}


void UDirLight::initialize(const Shader& shader, const String& baseName)
{
        base.initialize(shader, baseName + ".base");
        dir.initialize(shader, baseName + ".dir");
}

const UDirLight& UDirLight::operator=(const DirLight& light) const
{
        base = static_cast<const LightBase&>(light);
        dir = light.dir;
        return *this;
}

void UPointLight::initialize(const Shader& shader, const String& baseName)
{
        base.initialize(shader, baseName + ".base");
        att.cst.initialize(shader, baseName + ".att.cst");
        att.exp.initialize(shader, baseName + ".att.exp");
        att.linear.initialize(shader, baseName + ".att.linear");
        pos.initialize(shader, baseName + ".pos");
}

const UPointLight& UPointLight::operator=(const PointLight& light) const
{
        base = static_cast<const LightBase&>(light);
        att.cst = light.att.cst;
        att.exp = light.att.exp;
        att.linear = light.att.linear;
        pos = light.getPos();
        return *this;
}

void USpotLight::initialize(const Shader& shader, const String& baseName)
{
        base.initialize(shader, baseName + ".base");
        dir.initialize(shader, baseName + ".dir");
        cutOff.initialize(shader, baseName + ".cutOff");
        outerCutOff.initialize(shader, baseName + ".outerCutOff");
}

const USpotLight& USpotLight::operator=(const SpotLight& light) const
{
        base   = static_cast<const PointLight&>(light);
        dir    = glm::normalize(light.target - light.getPos());//light.dir;
        cutOff = light.cutOff;
        outerCutOff = light.outerCutOff;
        return *this;
}

void UMaterial::initialize(const Shader& shader, const String& baseName)
{
        ambient.initialize(shader, baseName + ".ambient");
        diffuse.initialize(shader, baseName + ".diffuse");
        specular.initialize(shader, baseName + ".specular");
        specularIntensity.initialize(shader, baseName + ".specularIntensity");
}

const UMaterial& UMaterial::operator=(const Material& mat) const
{
        ambient = mat.ambient;
        diffuse = mat.diffuse;
        specular = mat.specular;
        specularIntensity = mat.specularIntensity;
        return *this;
}

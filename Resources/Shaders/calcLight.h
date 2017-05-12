#ifndef CALC_LIGHT_H
#define CALC_LIGHT_H

#include "common.h"

struct LightInfo
{
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
};

vec3 calcLight(LightInfo i, vec3 col)
{
        return (i.ambient + i.diffuse + i.specular) * col;
}

LightInfo calcLightBaseInfo(LightBase base, vec3 lightDir)
{
        float diff      = max(dot(g_Norm, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, g_Norm);
        float spec      = pow(max(dot(g_ViewDir, reflectDir), 0.0), g_Material.specularIntensity);

        LightInfo info;
        info.ambient  = vec3(base.ambient)  * g_Material.ambient;// * vec3(texture(material.diffuse, TexCoords));
        info.diffuse  = vec3(base.diffuse)  * vec3(diff * g_Material.diffuse);// * diff * vec3(texture(material.diffuse, TexCoords));
        info.specular = vec3(base.specular) * vec3(spec * g_Material.specular);// * spec * vec3(texture(material.specular, TexCoords));
        return info;
}

vec3 calcLightBase(LightBase base, vec3 lightDir)
{
     	return calcLight(calcLightBaseInfo(base, lightDir), base.col);
}

vec3 calcDirLight(DirLight light)
{
		return calcLightBase(light.base, normalize(-light.dir));
}

float attenuation(PointLight light, float dist)
{
		return 1.0 / (light.att.cst + light.att.linear * dist + light.att.exp * dist * dist);
}

LightInfo calcPointLightInfo(PointLight light)
{
        vec3 dir = light.pos - g_FragPos;
        LightInfo i = calcLightBaseInfo(light.base, normalize(dir));
        float att = attenuation(light, length(dir));
        i.ambient  *= att;
        i.diffuse  *= att;
        i.specular *= att;
        return i;
}

vec3 calcPointLight(PointLight light)
{
        return calcLight(calcPointLightInfo(light), light.base.col);
}

vec3 calcSpotLight(SpotLight light)
{
        vec3 dir = normalize(light.base.pos - g_FragPos);
        LightInfo i = calcPointLightInfo(light.base);

        float theta     = dot(dir, normalize(-light.dir)); 
        float epsilon   = (light.cutOff - light.outerCutOff);
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        i.diffuse  *= intensity;
        i.specular *= intensity;
    
        return calcLight(i, light.base.base.col);
}

vec4 calcLight()
{
		vec3 light = u_AmbientLight.col * u_AmbientLight.ambient;

		vec3 g_ViewDir = normalize(u_EyePos - g_FragPos);
		for (int i = 0; i < u_DirLights.count; i++)
				light += calcDirLight(u_DirLights.sources[i]);

		for (int i = 0; i < u_PointLights.count; i++)
				light += calcPointLight(u_PointLights.sources[i]);

		for (int i = 0; i < u_SpotLights.count; i++)
				light += calcSpotLight(u_SpotLights.sources[i]);

		return vec4(light, 1.0);
}

#endif

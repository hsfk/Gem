#define FRAGMENT_SHADER
#include "calcLight.h"

void main()
{
		g_Norm              = v_Norm;
		g_FragPos           = v_Pos;
		g_Material.ambient  = u_Material.ambient;
		g_Material.diffuse  = u_Material.diffuse;
		g_Material.specular = u_Material.specular;
		g_Material.specularIntensity = u_Material.specularIntensity;

		gl_FragColor = calcLight();//vec4(0.3, 0.3, 0.3, 1);//texture2D(u_Tex, v_UV) * 
}

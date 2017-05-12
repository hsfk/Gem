#include "common.h"

void main()
{
		v_Pos   = vec3(u_Model * vec4(a_Pos, 1.0));
		v_Norm  = normalize(a_Norm);
		v_UV    = a_UV;

		gl_Position = u_VP * u_Model * vec4(a_Pos, 1.0);
}
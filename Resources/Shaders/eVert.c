#include "common.h"

void main()
{
        gl_Position = u_VP * u_Model * vec4(a_Pos, 1.0);
}
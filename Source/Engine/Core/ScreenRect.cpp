#include "ScreenRect.h"

ScreenRect::ScreenRect()
{
        GLfloat v[] = 
        {
               -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
               -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        
        Engine::ext->glGenBuffers(1,&vertices);
        Engine::ext->glBindBuffer(GL_ARRAY_BUFFER, vertices);
        Engine::ext->glBufferData(GL_ARRAY_BUFFER, sizeof(v),&v, GL_STATIC_DRAW);
}

void ScreenRect::render()
{
        Engine::ext->glBindBuffer(GL_ARRAY_BUFFER, vertices);
        Engine::ext->glEnableVertexAttribArray(0);
        Engine::ext->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        Engine::ext->glEnableVertexAttribArray(1);
        Engine::ext->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

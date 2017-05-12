#pragma once

#include "Types.h"

struct Config
{
        Config() : screenWidth(1024), screenHeight(768)
        {
        }
        
        int screenWidth;
        int screenHeight;

        GLfloat aspectRatio() const
        {
                return GLfloat(screenWidth) / GLfloat(screenHeight);
        }
};

#pragma once

#include "Core/Common.h"

struct GBuffer
{
        enum TextureKind
        {
                tkPosition,
                tkNormal,
                tkAlbedo,
                tkSize
        };

        void initialize(int width, int height);
        void bind() const;
        void unbind() const;

        int width;
        int height;

        GLuint fbo;
        GLuint depth;

        GLuint tex[tkSize];
};

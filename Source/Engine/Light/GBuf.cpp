#include "GBuf.h"
#include "Core/Common.h"

#if MRT_SUPPORTED

void GBuffer::initialize(int width, int height)
{
        this->width = width;
        this->height = height;

        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        GLint iFormat[] = { GL_RGB16F, GL_RGB16F, GL_RGBA };
        GLenum format[] = { GL_RGB, GL_RGB, GL_RGBA };
        GLenum type[] = { GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE };
        for (int i = 0; i < TextureKind::tkSize; i++)
        {
                glGenTextures(1, tex + i);
                glBindTexture(GL_TEXTURE_2D, tex[i]);
                glTexImage2D(GL_TEXTURE_2D, 0, iFormat[i], width, height, 0, format[i], type[i], NULL);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex[i], 0);
        }

        GLenum att[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glDrawBuffers(3, att);
        
        glGenRenderbuffers(1, &depth);
        glBindRenderbuffer(GL_RENDERBUFFER, depth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);
        
        jassert(Engine::ext->glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::bind() const
{
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void GBuffer::unbind() const
{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#else

void GBuffer::initialize(int width, int height)
{
}

void GBuffer::bind() const
{
}

void GBuffer::unbind() const
{
}

#endif

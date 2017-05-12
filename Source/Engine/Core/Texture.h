#pragma once

#include "Buffer.h"
#include <JuceHeader.h>

using juce::String;
using juce::Image;
using juce::OpenGLTexture;

class Texture : public OpenGLTexture, public Serial
{
public:
        Texture(GLint wrapMode = GL_REPEAT);
        Texture(const Texture& tex);
        Texture(const String& abs, GLint wrapMode = GL_REPEAT);
        Texture(const File& file , GLint wrapMode = GL_REPEAT);
        Texture(const Image& image, GLint wrapMode = GL_REPEAT);
        bool valid() const;
        
        virtual void save(Ostream& out) const override;
        virtual void load(Istream& in) override;
        DECLARE_SERIAL(Texture)

        GLint wrapMode;
        Image image;
};

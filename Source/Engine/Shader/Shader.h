#pragma once

#include "Core/Types.h"

struct ShaderData
{
        ShaderData() = default;
        ShaderData(const String& v, const String& f)
                : vertex(v), fragment(f)
        {
        }
        ShaderData(const ShaderData& other)
                : ShaderData(other.vertex, other.fragment)
        {
        }

        String vertex;
        String fragment;
};

class Shader : public juce::OpenGLShaderProgram
{
public:
        Shader(const OpenGLContext& context)
                : OpenGLShaderProgram(context)
        {
        }

        Shader(const OpenGLContext& context, const ShaderData& sd)
                : Shader(context)
        {
                initialize(sd);
        }

        void initialize(const ShaderData& sd)
        {
                addVertexShader(sd.vertex);
                addFragmentShader(sd.fragment);
                jassert(link());
        }
};
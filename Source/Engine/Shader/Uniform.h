#pragma once

#include "Core/Common.h"
#include "Core/Math.h"
#include "Core/Types.h"
#include "Core/Texture.h"
#include "Shader.h"

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

struct Sampler2D
{
        Sampler2D() = default;

        Sampler2D(GLint id)
                : id(id)
        {
        }

        Sampler2D(const Texture& tex)
                : id(tex.getTextureID())
        {
        }

        Sampler2D& operator=(const GLint& id)
        {
                this->id = id;
                return *this;
        }

        GLint id;
};

template <typename T>
struct Uniform
{
        typedef T Type;

        void initialize(const Shader& shader, const String& name);

        void set(const T& val) const;

        const Uniform& operator=(const T& val) const
        {
                set(val);
                return *this;
        }

        GLint val;
};

template<typename T>
inline void Uniform<T>::initialize(const Shader& shader, const String& name)
{
        val = shader.getUniformIDFromName(name.getCharPointer());
        if (val == INVALID_UNIFORM_LOCATION)
                DBG(name + " shader uniform is not valid.");
}

template<>
inline void Uniform<GLfloat>::set(const GLfloat& val) const
{
        Engine::ext->glUniform1f(this->val, val);
}

template<>
inline void Uniform<GLint>::set(const GLint& val) const
{
        Engine::ext->glUniform1i(this->val, val);
}

template<>
inline void Uniform<Vec3D>::set(const Vec3D& val) const
{
        Engine::ext->glUniform3f(this->val, val.x, val.y, val.z);
}

template<>
inline void Uniform<Mat4D>::set(const Mat4D& val) const
{
        Engine::ext->glUniformMatrix4fv(this->val, 1, GL_FALSE, glm::value_ptr(val));
}

template<>
inline void Uniform<Mat3D>::set(const Mat3D& val) const
{
        Engine::ext->glUniformMatrix3fv(this->val, 1, GL_FALSE, glm::value_ptr(val));
}

template<typename T>
inline void Uniform<T>::set(const T& val) const
{
        jassert(0); // todo
}

template <>
struct Uniform<Sampler2D>
{
        void initialize(const Shader& shader, const String& name, GLenum index = 0)
        {
                val = shader.getUniformIDFromName(name.getCharPointer());
                idx = index;
                if (val == INVALID_UNIFORM_LOCATION)
                        DBG(name + " shader uniform is not valid.");
        }
        
        const Uniform& operator=(const Sampler2D& val) const
        {
                Engine::ext->glUniform1i(this->val, idx);
                Engine::ext->glActiveTexture(GL_TEXTURE0 + idx);
                glBindTexture(GL_TEXTURE_2D, val.id);
                return *this;
        }
        
        GLenum idx;
        GLint val;
};

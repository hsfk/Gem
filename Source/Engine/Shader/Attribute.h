#pragma once

#include "Core/Common.h"
#include "Core/Buffer.h"
#include "Shader.h"

#define INVALID_ATTRIBUTE_LOCATION 0xFFFFFFFF

template <typename T>
struct Attribute
{
        typedef T Type;

        Attribute() = default;

        Attribute(const Shader& shader, const String& name)
        {
                initialize(shader, name);
        }

        void initialize(const Shader& shader, const String& name)
        {
                location = Engine::ext->glGetAttribLocation(shader.getProgramID(), name.getCharPointer());
                if (location == INVALID_ATTRIBUTE_LOCATION)
                        DBG(name + " attribute is not valid.");
        }

        void set(const T& val) const;

        const Attribute& operator=(const T& val) const
        {
                set(val);
                return *this;
        }

        GLuint location;
};

template<typename T>
inline void Attribute<T>::set(const T& val) const
{
        jassertfalse;
}

template<typename T, GLint Size, GLenum Type>
inline void bindVertexAtt(const Buffer<T>& buf, GLuint location)
{
        Engine::ext->glBindBuffer(buf.kind, buf.handler);
        Engine::ext->glVertexAttribPointer(location, Size, Type, GL_FALSE, sizeof(T), (GLvoid*)0);
        Engine::ext->glEnableVertexAttribArray(location);
}

template<>
inline void Attribute<Buffer<Vec3D>>::set(const Buffer<Vec3D>& buf) const
{
        // Normals and Vertices
        bindVertexAtt<Vec3D, 3, GL_FLOAT>(buf, location);
}

template<>
inline void Attribute<TextureCoords>::set(const TextureCoords& coords) const
{
        bindVertexAtt<TextureCoords::value_type, 2, GL_FLOAT>(coords, location);
}

template<>
inline void Attribute<Indices>::set(const Indices& indices) const
{
        Engine::ext->glBindBuffer(indices.kind, indices.handler);
}

#pragma once

#include "Types.h"

template <typename T, GLenum BufKind = GL_ARRAY_BUFFER, GLenum BufUsage = GL_STATIC_DRAW>
class Buffer : public Vector<T>
{
public:
        Buffer()
                : kind(BufKind), usage(BufUsage), handler(-1)
        {
        }
        
        Buffer(const Buffer& buf)
                : Vector<T>(buf), kind(BufKind), usage(BufUsage), handler(buf.handler)
        {
        }

        Buffer(std::initializer_list<T> l)
                : Buffer()
        {
                const T* it = l.begin();
                this->resize(l.size());
                for (size_t i = 0; it != l.end(); it++, i++)
                        (*this)[i] = *it;
        }
        
        size_t byteSize() const
        {
                return sizeof(T) * this->size();
        }
        
        virtual void save(Ostream& out) const override
        {
                Vector<T>::save(out);
                out < GLuint(-1) < kind < usage;
        }

        virtual void load(Istream& in) override
        {
                Vector<T>::load(in);
                in > handler > kind > usage;
        }

        DECLARE_SERIAL(Buffer)

        GLuint handler;
        GLenum kind;
        GLenum usage;
};

typedef Buffer<Vec3D> Vertices;
typedef Buffer<Vec2D> TextureCoords;
typedef Buffer<Vec3D> Normals;
typedef Buffer<GLuint, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW> Indices;

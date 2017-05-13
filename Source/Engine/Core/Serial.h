#pragma once

#include <type_traits>
#include <map>
#include <JuceHeader.h>

struct Istream;
struct Ostream;

typedef uint64_t TypeID;

struct TypeInfo
{
        TypeInfo() = default;
        TypeInfo(TypeID id, const char* name) : id(id), name(name) {}
        TypeInfo(const TypeInfo& other) : TypeInfo(other.id, other.name) {}

        TypeID id;
        const char* name;
};

template <typename T>
struct MakeTypeInfo
{
        TypeInfo operator()() const
        {
                return TypeInfo(typeid(T).hash_code(), typeid(T).name());
        }
};

struct Serial;

struct Constructor
{
        virtual void* operator()(Istream& in) = 0;
};

template <typename T>
struct DefaultConstructor : Constructor
{
        virtual void* operator()(Istream& in) override
        {
                T* obj = new T();
                obj->load(in);
                return obj;
        }
};

class SerialTypeInfo
{
        typedef std::map<TypeID, Constructor*> ConstructorMap;
public:
        static bool registered(TypeID id);

        template <typename T>
        static void regType(Constructor* ctor)
        {
                TypeID id = typeid(T).hash_code();
                if (ctors.find(id) != ctors.end())
                        return;
                jassert(ctor);
                ctors.insert(std::make_pair(id, ctor));
        }

        template <typename T>
        static void regType()
        {
                regType<T>(new DefaultConstructor<T>());
        }

        static Constructor& getConstructor(TypeID id)
        {
                ConstructorMap::iterator it = ctors.find(id);
                jassert(it != ctors.end());
                return *it->second;
        }

        static void clear();

private:

        static ConstructorMap ctors;
};

class Istream
{
public:
        template <typename T>
        inline Istream& operator>(T& value)
        {
                load(&value, sizeof(T));
                return *this;
        }

        template<typename T>
        inline T read()
        {
                T val;
                load(&val, sizeof(T));
                return val;
        }

        Istream& operator>>(void** serial);
        Istream& operator>>(Serial& serial);
        Istream& operator>>(Image& image);
        Istream& operator>>(String& string);

protected:
        virtual void load(void* buf, size_t size) = 0;
};

class Ostream
{
        template <typename T>
        struct Out;

public:
        template <typename T>
        inline Ostream& operator<(const T& value)
        {
                save(&value, sizeof(T));
                return *this;
        }

        Ostream& operator<<(const Serial& serial);
        Ostream& operator<<(const String& string);
        Ostream& operator<<(const Image& image);
        virtual void save(const void* data, size_t size) = 0;
};

class JIstream : public Istream
{
public:
        JIstream(const File& file);

protected:
        virtual void load(void* buf, size_t size) override;

private:
        FileInputStream in;
};

class JOstream : public Ostream
{
public:
        JOstream(const File& file);
        ~JOstream();

protected:
        virtual void save(const void* data, size_t size) override;

private:
        FileOutputStream out;
};

struct Serial
{
        virtual void save(Ostream& out) const = 0;
        virtual void load(Istream& in) = 0;
        virtual TypeInfo typeInfo() const = 0;

        void saveToFile(const String& path) const;
        void loadFromFile(const String& path);
};

#define DECLARE_SERIAL(TYPE) \
        virtual TypeInfo typeInfo() const override { return MakeTypeInfo<TYPE>()(); }

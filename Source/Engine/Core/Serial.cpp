#include "Serial.h"

SerialTypeInfo::ConstructorMap SerialTypeInfo::ctors;

Istream& Istream::operator>>(void** serial)
{
        *serial = SerialTypeInfo::getConstructor(read<TypeID>())(*this);
        return *this;
}

Istream& Istream::operator>>(Serial& serial)
{
        read<TypeID>();
        serial.load(*this);
        return *this;
}

Istream& Istream::operator>>(Image& image)
{
        int width, height;
        Image::PixelFormat format;
        *this > format > width > height;

        image = Image(format, width, height, false);
        for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                        image.setPixelAt(x, y, read<Colour>());

        return *this;
}

Istream& Istream::operator>>(String& string)
{
        int length = read<int>();
        for (int i = 0; i < length; i++)
                string += read<juce_wchar>();
        return *this;
}

Ostream& Ostream::operator<<(const Serial& serial)
{
        TypeInfo info = serial.typeInfo();

        if (!SerialTypeInfo::registered(info.id))
                DBG("Serial.h: Type " << info.name << " is not registered.");

        *this < info.id;
        serial.save(*this);
        return *this;
}

Ostream& Ostream::operator<<(const String& string)
{
        *this < string.length();
        for (int i = 0; i < string.length(); i++)
                *this < string[i];
        return *this;
}

Ostream& Ostream::operator<<(const Image& image)
{
        int width = image.getWidth();
        int height = image.getHeight();
        *this < image.getFormat() < width < height;

        for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                        *this < image.getPixelAt(x, y);
        return *this;
}

JIstream::JIstream(const File& file)
        : in(file)
{
}

void JIstream::load(void* buf, size_t size)
{
        size_t read = in.read(buf, int(size));

        // missing bytes
        jassert(read == size);
}

JOstream::JOstream(const File& file)
        : out(file)
{
}

JOstream::~JOstream()
{
        out.flush();
}

void JOstream::save(const void* data, size_t size)
{
        bool res = out.write(data, size);
        jassert(res);
}

bool SerialTypeInfo::registered(TypeID id)
{
        return ctors.find(id) != ctors.end();
}

void SerialTypeInfo::clear()
{
        ctors.clear();
}

void Serial::saveToFile(const String& path) const
{
        File f = File::getCurrentWorkingDirectory().getChildFile(path);
        if (f.exists())
                f.deleteFile();
        f.create();
        JOstream out(f);
        save(out);
}

void Serial::loadFromFile(const String& path)
{
        File f = File::getCurrentWorkingDirectory().getChildFile(path);
        jassert(f.exists());
        JIstream in(f);
        load(in);
}

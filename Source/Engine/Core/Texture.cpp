#include "Texture.h"

Texture::Texture(const Image& image, GLint wrapMode)
        : image(image), wrapMode(wrapMode)
{
}

Texture::Texture(GLint wrapMode)
        : wrapMode(wrapMode)
{
}

Texture::Texture(const Texture& tex)
        : Texture(tex.image, tex.wrapMode)
{
}

Texture::Texture(const String& abs, GLint wrapMode)
        : Texture(File(abs), wrapMode)
{
}

Texture::Texture(const File& file, GLint wrapMode)
        : wrapMode(wrapMode)
{
        jassert(file.exists());
        image = ImageCache::getFromFile(file);
        jassert(valid());
        ImageCache::releaseUnusedImages();
}

bool Texture::valid() const
{
        return image.isValid();
}

void Texture::save(Ostream& out) const
{
        out << image < wrapMode;
}

void Texture::load(Istream& in)
{
        in >> image > wrapMode;
}

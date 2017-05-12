#include "Resource.h"
#include "Scene/Import.h"

void dump(const String& file, const String& data)
{
        File f = File::getCurrentWorkingDirectory().getChildFile(file);
        if (f.exists())
                f.deleteFile();
        f.create();
        f.appendText(data);
}

Resources::Resources()
{
        initialize(defaultDir());
}

Resources::Resources(const File& dir)
{
        initialize(dir);
}

void Resources::initialize(const File& dir)
{
        this->dir = dir;
}

Mesh Resources::Meshes::loadRectMesh()
{
        Vertices v({
                Vec3D(-0.5,  0.5, 0.0),
                Vec3D( 0.5,  0.5, 0.0),
                Vec3D( 0.5, -0.5, 0.0),
                Vec3D(-0.5, -0.5, 0.0)
        });

        Indices i({
                0, 1, 2,
                0, 2, 3
        });
        return Mesh(v, i);
}

Mesh Resources::Meshes::loadCubeMesh()
{
        Vertices v({
                Vec3D(-0.5,  0.5, -0.5),
                Vec3D( 0.5,  0.5, -0.5),
                Vec3D( 0.5, -0.5, -0.5),
                Vec3D(-0.5, -0.5, -0.5),
                Vec3D(-0.5,  0.5,  0.5),
                Vec3D( 0.5,  0.5,  0.5),
                Vec3D( 0.5, -0.5,  0.5),
                Vec3D(-0.5, -0.5,  0.5)
        });
        Indices i({
                0, 1, 2,
                0, 2, 3,
                4, 5, 6,
                4, 6, 7,
                6, 1, 2,
                6, 5, 1,
                7, 0, 3,
                7, 4, 0,
                7, 2, 3,
                7, 6, 2,
                4, 1, 0,
                4, 5, 1
        });
        return Mesh(v, i);
}

Mesh Resources::Meshes::loadCubeFaceMesh(int face)
{
        Point3D p1(-0.5,  0.5, -0.5);
        Point3D p2( 0.5,  0.5, -0.5);
        Point3D p3( 0.5, -0.5, -0.5);
        Point3D p4(-0.5, -0.5, -0.5);
        Point3D p5(-0.5,  0.5,  0.5);
        Point3D p6( 0.5,  0.5,  0.5);
        Point3D p7( 0.5, -0.5,  0.5);
        Point3D p8(-0.5, -0.5,  0.5);
        
        Point3D nx(1, 0, 0);
        Point3D ny(0, 1, 0);
        Point3D nz(0, 0, 1);

        switch (face)
        {
                case 0: return Mesh(Mesh::fromRectangle(p1, p2, p3, p4, -nz));
                case 1: return Mesh(Mesh::fromRectangle(p1, p5, p6, p2,  ny));
                case 2: return Mesh(Mesh::fromRectangle(p1, p5, p8, p4, -nx));
                case 3: return Mesh(Mesh::fromRectangle(p5, p6, p7, p8,  nz));
                case 4: return Mesh(Mesh::fromRectangle(p2, p6, p7, p3,  nx));
                case 5: return Mesh(Mesh::fromRectangle(p3, p7, p8, p4, -ny));

                default: jassertfalse;
        }
}

Mesh Resources::Meshes::loadTriangleMesh()
{
        Vertices v({
                Vec3D(-0.5, -0.5, 0.0),
                Vec3D( 0.5, -0.5, 0.0),
                Vec3D( 0.0,  0.5, 0.0)
        });
        Indices i({ 0, 1, 2 });
        return Mesh(v, i);
}

File Resources::defaultDir()
{
        return File::getCurrentWorkingDirectory()
                .getParentDirectory()
                .getChildFile("Resources");
}

Texture* Resources::loadTexture(const String& tex)
{
        return loadSquareTexture(getTextureDir().getChildFile(tex));
}

Asset Resources::loadAsset(const String& obj, const String& matDir)
{
        return Importer::importAsset(getAssetDir().getChildFile(obj), getAssetDir().getChildFile(matDir));
}

Texture* Resources::loadSquareTexture(const File& tex, float s, GLint wrapMode)
{
        return new Texture(tex.getFullPathName(), wrapMode);
}

String Resources::loadShaderCode(const String& shader)
{
        return loadShaderCode(getShaderDir().getChildFile(shader));
}

String Resources::loadShaderCode(const File & shader)
{
        String code = loadShaderCodeImpl(shader);
#if DEBUG
        dump(shader.getFileName(), code);
#endif
        return code;
}

File Resources::getTextureDir() const
{
        return dir.getChildFile("Textures");
}

File Resources::getShaderDir() const
{
        return dir.getChildFile("Shaders");
}

File Resources::getAssetDir() const
{
        return dir.getChildFile("Assets");
}

String Resources::loadShaderCodeImpl(const File& shader)
{
        jassert(shader.exists());
        File dir = shader.getParentDirectory();

        StringArray lines;
        shader.readLines(lines);

        for (size_t i = 0; i < lines.size(); i++)
                preprocessLine(lines.getReference(i), dir);

        return lines.joinIntoString("\n");
}

void Resources::preprocessLine(String& line, const File& parentDir)
{
        static const char include[] = "#include";
        static const int qBegin = sizeof(include) - 1;

        String trimmed = line.removeCharacters(" ").trim();
        if (trimmed.length() < sizeof(include))
                return;
        for (int j = 0; j < sizeof(include) - 1; j++)
                if (trimmed[j] != include[j])
                        return;

        jassert(trimmed[qBegin] == '\"' && trimmed[trimmed.length() - 1] == '\"');

        String file = trimmed.substring(qBegin).unquoted();
        File inc = parentDir.getChildFile(file);
        line = loadShaderCode(parentDir.getChildFile(file));
}

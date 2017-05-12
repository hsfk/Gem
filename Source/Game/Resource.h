#pragma once

#include "Engine.h"

void dump(const String& file, const String& data);

class Resources
{
public:
        Resources();
        Resources(const File& dir);

        void initialize(const File& dir);

        struct Meshes
        {
                static Mesh loadRectMesh();
                static Mesh loadTriangleMesh();
                static Mesh loadCubeMesh();
                static Mesh loadCubeFaceMesh(int face);
        };
        static File defaultDir();

        Texture* loadTexture(const String& tex);
        Asset    loadAsset(const String& obj, const String& matDir);
        String   loadShaderCode(const String& shader);
        String   loadShaderCode(const File& shader);

        File     getTextureDir() const;
        File     getShaderDir() const;
        File     getAssetDir() const;

protected:
        Texture* loadSquareTexture(const File& tex, float s = 1.0, GLint wrapMode = GL_REPEAT);

        File dir;

private:
        String loadShaderCodeImpl(const File& shader);
        void   preprocessLine(String& line, const File& parentDir);
};
#include "Import.h"
#include "ImportImpl.h"

Asset Importer::importAsset(const File& model, const File& matDir)
{
        return importAsset(model.getFullPathName(), File::addTrailingSeparator(matDir.getFullPathName()));
}

Asset Importer::importAsset(const String& model, const String& matDir)
{
        return ObjImporter::importAsset(model, matDir);
}

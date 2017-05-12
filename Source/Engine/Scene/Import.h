#pragma once

#include "Asset.h"

class Importer
{
public:
        static Asset importAsset(const String& model, const String& matDir);
        static Asset importAsset(const File& model, const File& matDir);
};
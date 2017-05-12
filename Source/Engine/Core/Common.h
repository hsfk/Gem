#pragma once

#include <JuceHeader.h>

struct Engine
{
        static void init(OpenGLExtensionFunctions* e, OpenGLContext* c);

        static OpenGLExtensionFunctions* ext;
        static OpenGLContext*            context;
};

#if __APPLE__
#define MRT_SUPPORTED 1
#else
#define MRT_SUPPORTED 0
#endif


#pragma once
#include "TextureBase.hpp"

namespace Flicker
{
    struct ImageData
    {
        int width, height, numComponents;
        unsigned char* data;

        ImageData(int width, int height, int numComponents, unsigned char* data)
            : width(width), height(height), numComponents(numComponents), data(data) {}
    };
    

    class Cubemap : public TextureBase
    {
    public:
    
        Cubemap (const std::vector<ImageData>& facesData);
        virtual ~Cubemap();

    };
}
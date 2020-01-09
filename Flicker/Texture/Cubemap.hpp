#pragma once
#include "TextureBase.hpp"

namespace Flicker
{
    struct ImageData
    {
        int width, height;
        unsigned char* data;

        ImageData(int width, int height, unsigned char* data)
            : width(width), height(height), data(data) {}
    };
    

    class Cubemap : public TextureBase
    {
    public:
    
        Cubemap (const std::vector<ImageData>& facesData);
        virtual ~Cubemap();

    };
}
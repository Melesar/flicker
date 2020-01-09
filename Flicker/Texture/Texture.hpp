#pragma once
#include "TextureBase.hpp"

namespace Flicker
{
    class Texture : public TextureBase
    {
    public:

        int width() const;
        int height() const;

        Texture(int width, int height, unsigned char* data);
        virtual ~Texture();

    private:

        int m_Width, m_Height;
    };
}
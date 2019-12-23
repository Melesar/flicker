#pragma once

namespace Flicker
{
    class Texture
    {
    public:

        int width() const;
        int height() const;

        GLuint id() const;

        Texture(int width, int height, unsigned char* data);
        ~Texture();

    private:

        int m_Width, m_Height;
        GLuint m_Id;
    };
}
#include "Texture.hpp"

int Flicker::Texture::width() const
{
    return m_Width;
}

int Flicker::Texture::height() const
{
    return m_Height;
}

GLuint Flicker::Texture::id() const
{
    return m_Id;
}

Flicker::Texture::Texture(int width, int height, unsigned char* data) 
    : m_Width(width), m_Height(height)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Flicker::Texture::~Texture()
{
    glDeleteTextures(1, &m_Id);
}
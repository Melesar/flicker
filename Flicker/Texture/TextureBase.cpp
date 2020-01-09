#include "TextureBase.hpp"

GLuint Flicker::TextureBase::id() const
{
    return m_Id;
}

Flicker::TextureBase::TextureBase(int numTextures)
{
    glGenTextures(numTextures, &m_Id);
    m_NumTextures = numTextures;
}

Flicker::TextureBase::~TextureBase()
{
    glDeleteTextures(m_NumTextures, &m_Id);
}
#include "Cubemap.hpp"

Flicker::Cubemap::Cubemap(const std::vector<ImageData>& facesData) : TextureBase(1)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
    for (size_t i = 0; i < facesData.size(); i++)
    {
        const ImageData& faceImage = facesData[i];
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, faceImage.width, faceImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, faceImage.data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Flicker::Cubemap::~Cubemap()
{
    
}
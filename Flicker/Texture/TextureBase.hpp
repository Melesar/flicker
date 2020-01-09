#pragma once 

namespace Flicker
{
    class TextureBase
    {
    public:
    
        GLuint id() const;
        virtual ~TextureBase();

    protected:

        TextureBase(int numTextures);
    
    protected:

        GLuint m_Id;

    private:

        int m_NumTextures;
    };
}
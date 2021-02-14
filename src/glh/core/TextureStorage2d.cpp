#include "Image.hpp"
#include "TextureStorage2d.hpp"
#include <glad/glad.h>
#include <stdexcept>

glh::TextureStorage2d::TextureStorage2d()
    : AbstractTexture()
{
    mTarget = GL_TEXTURE_2D;
}

glh::TextureStorage2d::~TextureStorage2d()
{
    destroy();
}

void glh::TextureStorage2d::loadFromFile(const std::string& fileName)
{
    glh::Image img;

    if(img.loadFromFile(fileName)) {

        create();

        mInternalFormat = GL_RGBA;

        mWidth = img.getWidth();
        mHeight = img.getHeight();

        glTexStorage2D(mTarget, 1, GL_RGB8, mWidth, mHeight);
        glTexSubImage2D(mTarget, 0, 0, 0, mWidth, mHeight, mInternalFormat, GL_UNSIGNED_BYTE, img.getPixelsPtr());
        generateMipMap();
        unbind();

    } else
        throw std::runtime_error(std::string("glh::Texture2d : failed to load image " + fileName));
}

void glh::TextureStorage2d::texture2d(const int width,
    const int height,
    const GLenum internalFormat,
    const GLenum format,
    const GLenum glType,
    void* data)
{
    mWidth = width;
    mHeight = height;
    mInternalFormat = internalFormat;

    create();

    glTexImage2D(mTarget, 0, mInternalFormat, mWidth, mHeight, 0, format, glType, data);
}

void glh::TextureStorage2d::generateMipMap()
{
    glGenerateMipmap(mTarget);
}

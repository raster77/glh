#include "Texture2d.hpp"
#include "Image.hpp"
#include <stdexcept>

glh::Texture2d::Texture2d()
    : AbstractTexture()
{
    mTarget = GL_TEXTURE_2D;
    mInternalFormat = GL_RGBA;
}

glh::Texture2d::~Texture2d()
{
    destroy();
}

void glh::Texture2d::loadFromFile(const std::string& fileName)
{
    glh::Image img;

    if(img.loadFromFile(fileName)) {

        create();
        mWidth = img.getWidth();
        mHeight = img.getHeight();
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(mTarget, 0, mInternalFormat, mWidth, mHeight, 0, mInternalFormat, GL_UNSIGNED_BYTE, img.getPixelsPtr());
        checkGlError("glh::Texture2d::loadFromFile");

    } else
        throw std::runtime_error(std::string("glh::Texture2d : failed to load image " + fileName));
}

void glh::Texture2d::texture2d(const int width, const int height, const GLenum internalFormat, const GLenum format, const GLenum glType, void* data)
{
    mWidth = width;
    mHeight = height;
    mInternalFormat = internalFormat;

    create();

    glTexImage2D(mTarget, 0, mInternalFormat, mWidth, mHeight, 0, format, glType, data);
    checkGlError("glh::Texture2d::texture2d");
}

void glh::Texture2d::generateMipMap()
{
    glGenerateMipmap(mTarget);
    checkGlError("glh::Texture2d::generateMipMap");
}

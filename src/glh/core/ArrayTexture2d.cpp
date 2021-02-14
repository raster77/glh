#include "ArrayTexture2d.hpp"
#include "glh/core/Image.hpp"

glh::ArrayTexture2d::ArrayTexture2d()
    : AbstractTexture()
{
    mTarget = GL_TEXTURE_2D_ARRAY;
}

glh::ArrayTexture2d::~ArrayTexture2d()
{
    destroy();
}

void glh::ArrayTexture2d::create(const unsigned int width,
    const unsigned int height,
    const unsigned int layers,
    const GLint internalFormat,
    const GLenum format,
    const GLenum glType)
{
    if(mId == 0) {
        mWidth = width;
        mHeight = height;
        AbstractTexture::create();
        glTexImage3D(mTarget, 0, internalFormat, width, height, layers, 0, format, glType, nullptr);
    }
}

void glh::ArrayTexture2d::add(const unsigned int layer, void* data, const GLenum format, const GLenum glType)
{
    if(mId > 0) {
        glTexSubImage3D(mTarget, 0, 0, 0, layer, mWidth, mHeight, 1, format, glType, data);
    }
}

void glh::ArrayTexture2d::addFromFile(const unsigned int layer,
    const std::string fileName,
    const GLenum format,
    const GLenum glType)
{
    if(mId > 0) {
        glh::Image img;

        if(img.loadFromFile(fileName)) {

            mInternalFormat = GL_RGBA;

            glTexSubImage3D(mTarget, 0, 0, 0, layer, mWidth, mHeight, 1, format, glType, img.getPixelsPtr());
            checkGlError("glh::ArrayTexture2d::addFromFile");
        }
    }
}

void glh::ArrayTexture2d::generateMipMap()
{
    glGenerateMipmap(mTarget);
    checkGlError("glh::ArrayTexture2d::generateMipMap");
}
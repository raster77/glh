#include "ArrayTextureStorage2d.hpp"
#include "glh/core/Image.hpp"

glh::ArrayTextureStorage2d::ArrayTextureStorage2d()
    : AbstractTexture()
{
    mTarget = GL_TEXTURE_2D_ARRAY;
}

glh::ArrayTextureStorage2d::~ArrayTextureStorage2d()
{
    destroy();
}

void glh::ArrayTextureStorage2d::create(const int level, const unsigned int width, const unsigned int height, const int depth, const GLenum internalFormat)
{
    if(mId == 0) {
        mWidth = width;
        mHeight = height;
        AbstractTexture::create();
        glTexStorage3D(mTarget, level, internalFormat, width, height, depth);
    }
}

void glh::ArrayTextureStorage2d::add(const unsigned int layer, void* data, const GLenum format, const GLenum glType)
{
    if(mId > 0) {
        glTexSubImage3D(mTarget, 0, 0, 0, layer, mWidth, mHeight, 1, format, glType, data);
    }
}

void glh::ArrayTextureStorage2d::addFromFile(const unsigned int layer, const std::string fileName, const GLenum format, const GLenum glType)
{
    if(mId > 0) {
        glh::Image img;

        if(img.loadFromFile(fileName)) {

            mInternalFormat = GL_RGBA;

            glTexSubImage3D(mTarget, 0, 0, 0, layer, mWidth, mHeight, 1, format, glType, img.getPixelsPtr());
            checkGlError("glh::ArrayTextureStorage2d::addFromFile");
        }
    }
}

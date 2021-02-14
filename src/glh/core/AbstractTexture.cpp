#include "AbstractTexture.hpp"
#include <iostream>

glh::AbstractTexture::AbstractTexture()
    : GlObject()
    , mTextureUnit(GL_TEXTURE0)
    , mTarget(0)
    , mInternalFormat(GL_RGB)
    , mWidth(0)
    , mHeight(0)
{
}

glh::AbstractTexture::~AbstractTexture()
{
    destroy();
}

const GLenum glh::AbstractTexture::getTextureUnit() const
{
    return mTextureUnit;
}

void glh::AbstractTexture::setTextureUnit(const GLenum textureUnit)
{
    mTextureUnit = textureUnit;
}

void glh::AbstractTexture::bindTextureUnit()
{
    glActiveTexture(mTextureUnit + mId);
    checkGlError("glh::AbstractTexture::glActiveTexture");
    bind();
}

void glh::AbstractTexture::bind()
{
    glBindTexture(mTarget, mId);
    checkGlError("glh::AbstractTexture::bind");
}

void glh::AbstractTexture::unbind()
{
    glBindTexture(mTarget, 0);
}

void glh::AbstractTexture::create()
{
    if(mId == 0) {
        glGenTextures(1, &mId);
        checkGlError("glh::AbstractTexture::create");
    }
    bind();
}

void glh::AbstractTexture::destroy()
{
    if(mId > 0) {
        glDeleteTextures(1, &mId);
        mId = 0;
    }
}

void glh::AbstractTexture::setParameter(const GLenum property, const int value)
{
    glTexParameteri(mTarget, property, value);
}

void glh::AbstractTexture::setParameter(const GLenum property, const float value)
{
    glTexParameterf(mTarget, property, value);
}

const int glh::AbstractTexture::getWidth() const
{
    return mWidth;
}

const int glh::AbstractTexture::getHeight() const
{
    return mHeight;
}

const GLenum glh::AbstractTexture::getTarget() const
{
    return mTarget;
}
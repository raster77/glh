#include "AbstractRenderBuffer.hpp"
#include <glad/glad.h>

glh::AbstractRenderBuffer::AbstractRenderBuffer()
    : GlObject()
    , mInternalFormat(GL_DEPTH24_STENCIL8)
    , mWidth(0)
    , mHeight(0)
{
}

glh::AbstractRenderBuffer::AbstractRenderBuffer(const unsigned int width, const unsigned int height)
    : mInternalFormat(GL_DEPTH24_STENCIL8)
    , mWidth(width)
    , mHeight(height)
{
}

glh::AbstractRenderBuffer::AbstractRenderBuffer(const unsigned int width, const unsigned int height, const GLenum internalFormat)
    : mInternalFormat(internalFormat)
    , mWidth(width)
    , mHeight(height)
{
}

glh::AbstractRenderBuffer::~AbstractRenderBuffer()
{
    destroy();
}

void glh::AbstractRenderBuffer::bind()
{
    if(mId > 0) {
        glBindRenderbuffer(GL_RENDERBUFFER, mId);
    }
}

void glh::AbstractRenderBuffer::destroy()
{
    if(mId > 0) {
        glDeleteRenderbuffers(1, &mId);
        mId = 0;
    }
}

void glh::AbstractRenderBuffer::unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

const GLenum glh::AbstractRenderBuffer::getInternalFormat() const
{
    return mInternalFormat;
}

void glh::AbstractRenderBuffer::setInternalFormat(const GLenum InternalFormat)
{
    mInternalFormat = InternalFormat;
}

const unsigned int glh::AbstractRenderBuffer::getWidth() const
{
    return mWidth;
}

void glh::AbstractRenderBuffer::setWidth(const unsigned int width)
{
    mWidth = width;
}

const unsigned int glh::AbstractRenderBuffer::getHeight() const
{
    return mHeight;
}

void glh::AbstractRenderBuffer::setHeight(const unsigned int height)
{
    mHeight = height;
}

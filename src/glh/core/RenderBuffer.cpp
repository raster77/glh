#include "RenderBuffer.hpp"

glh::RenderBuffer::RenderBuffer()
{
}

glh::RenderBuffer::RenderBuffer(const unsigned int width, const unsigned int height)
    : AbstractRenderBuffer(width, height)
{
}

glh::RenderBuffer::RenderBuffer(const unsigned int width, const unsigned int height, const GLenum internalFormat)
    : AbstractRenderBuffer(width, height, internalFormat)
{
}

glh::RenderBuffer::~RenderBuffer()
{
    destroy();
}

void glh::RenderBuffer::create(const unsigned int width, const unsigned int height, const GLenum internatFormat)
{
    if(mId == 0) {
        mWidth = width;
        mHeight = height;
        mInternalFormat = internatFormat;
        create();
    }
}

void glh::RenderBuffer::create()
{
    if(mId == 0) {
        glGenRenderbuffers(1, &mId);
        bind();
        checkGlError("glh::RenderBuffer::glGenRenderbuffers");
        glRenderbufferStorage(GL_RENDERBUFFER, mInternalFormat, mWidth, mHeight);
        checkGlError("glh::RenderBuffe::rglRenderbufferStorage");
    } else {
        bind();
    }
}

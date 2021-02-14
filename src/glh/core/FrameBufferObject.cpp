#include "FrameBufferObject.hpp"
#include "glad/glad.h"

glh::FrameBufferObject::FrameBufferObject()
    : GlObject()
{
}

glh::FrameBufferObject::~FrameBufferObject()
{
    destroy();
}

void glh::FrameBufferObject::bind()
{
    if(mId > 0) {
        glBindFramebuffer(GL_FRAMEBUFFER, mId);
    }
}

void glh::FrameBufferObject::create(const unsigned int width, const unsigned height)
{
    if(mId == 0) {
        mWidth = width;
        mHeight = height;
        create();
    }
}

void glh::FrameBufferObject::create()
{
    if(mId == 0) {
        glGenFramebuffers(1, &mId);
        checkGlError("glh::FrameBufferObject::create");
    }
    bind();
}

void glh::FrameBufferObject::attachTexture2d(GLenum attachement, const glh::AbstractTexture& texture)
{
    if(mId > 0) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachement, texture.getTarget(), texture.getId(), 0);
        checkGlError("glh::FrameBufferObject::attachTexture2d");
    }
}

void glh::FrameBufferObject::attachRenderBuffer(GLenum attachement, const glh::AbstractRenderBuffer& renderBuffer)
{
    if(mId > 0) {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachement, GL_RENDERBUFFER, renderBuffer.getId());
        checkGlError("glh::FrameBufferObject::attachRenderBuffer");
    }
}


void glh::FrameBufferObject::destroy()
{
    if(mId > 0) {
        glDeleteFramebuffers(1, &mId);
        mId = 0;
    }
}

void glh::FrameBufferObject::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const unsigned int glh::FrameBufferObject::getWidth() const
{
    return mWidth;
}

void glh::FrameBufferObject::setWidth(const unsigned int width)
{
    mWidth = width;
}

const unsigned int glh::FrameBufferObject::getHeight() const
{
    return mHeight;
}

void glh::FrameBufferObject::setHeight(const unsigned int height)
{
    mHeight = height;
}

bool glh::FrameBufferObject::isComplete()
{
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

GLenum glh::FrameBufferObject::getStatus()
{
    return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}

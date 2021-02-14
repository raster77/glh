#include "VertexBufferObject.hpp"

glh::VertexBufferObject::VertexBufferObject()
    : GlObject()
    , mTarget(GL_ARRAY_BUFFER)
    , mUsage(GL_STATIC_DRAW)
{
}

glh::VertexBufferObject::VertexBufferObject(GLenum target, GLenum usage)
    : GlObject()
    , mTarget(target)
    , mUsage(usage)
{
}

glh::VertexBufferObject::~VertexBufferObject()
{
    destroy();
}

void glh::VertexBufferObject::create(GLenum target, GLenum usage)
{
    setTargetAndUsage(target, usage);
    create();
}

void glh::VertexBufferObject::setTargetAndUsage(GLenum target, GLenum usage)
{
    setTarget(target);
    setUsage(usage);
}

void glh::VertexBufferObject::setTarget(GLenum target)
{
    if(mId == 0) {
        mTarget = target;
    }
}

const GLenum glh::VertexBufferObject::getTarget() const
{
    return mTarget;
}

void glh::VertexBufferObject::setUsage(GLenum usage)
{
    if(mId == 0) {
        mUsage = usage;
    }
}

const GLenum glh::VertexBufferObject::getUsage() const
{
    return mUsage;
}

void glh::VertexBufferObject::bind()
{
    glBindBuffer(mTarget, mId);
}

void glh::VertexBufferObject::bindRange(unsigned int index, unsigned int offset, unsigned int size)
{
    glBindBufferRange(mTarget, index, mId, offset, size);
}

void glh::VertexBufferObject::create()
{
    if(mId == 0) {
        glGenBuffers(1, &mId);
    }
    bind();
}
void glh::VertexBufferObject::destroy()
{
    if(mId > 0) {
        glDeleteBuffers(1, &mId);
        mId = 0;
    }
}
void glh::VertexBufferObject::unbind()
{
    glBindBuffer(mTarget, 0);
}

void* glh::VertexBufferObject::mapBufferRange(const unsigned int offset, const unsigned int length, GLenum access)
{
    if(mId > 0) {
        return glMapBufferRange(mTarget, offset, length, access);
    }
    return nullptr;
}

void glh::VertexBufferObject::setData(const void* data, const unsigned int size)
{
    if(mId > 0) {
        glBufferData(mTarget, static_cast<GLsizeiptr>(size), data, mUsage);
    }
}

void glh::VertexBufferObject::setSubData(const unsigned int offset, const unsigned int size, const void* data)
{
    if(mId > 0) {
        glBufferSubData(mTarget, offset, size, data);
    }
}

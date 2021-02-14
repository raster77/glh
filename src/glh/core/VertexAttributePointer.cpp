#include "VertexAttributePointer.hpp"
#include <iostream>
#include <algorithm>

glh::VertexAttributePointer::VertexAttributePointer()
    : mIndex(0)
    , mSize(0)
    , mGlType(GL_FLOAT)
    , mNormalized(false)
    , mStride(0)
    , mOffset(0)
    , created(false)
{
}

glh::VertexAttributePointer::VertexAttributePointer(const unsigned int index, const unsigned int size, const unsigned int stride, const unsigned int offset)
    : mIndex(index)
    , mSize(size)
    , mGlType(GL_FLOAT)
    , mNormalized(false)
    , mStride(stride)
    , mOffset(offset)
    , created(false)
{
}

glh::VertexAttributePointer::VertexAttributePointer(const unsigned int index, const unsigned int size, GLenum glType, const bool normalized, const unsigned int stride, const unsigned int offset)
    : mIndex(index)
    , mSize(size)
    , mGlType(glType)
    , mNormalized(normalized)
    , mStride(stride)
    , mOffset(offset)
    , created(false)
{
}

glh::VertexAttributePointer::~VertexAttributePointer()
{
//    disable();
}

void glh::VertexAttributePointer::setIndex(const unsigned int index)
{
    mIndex = index;
}

void glh::VertexAttributePointer::setSize(const unsigned int size)
{
    mSize = size;
}

void glh::VertexAttributePointer::setGlType(GLenum glType)
{
    mGlType = glType;
}

void glh::VertexAttributePointer::setNormalized(const bool normalized)
{
    mNormalized = normalized;
}

void glh::VertexAttributePointer::setStride(const unsigned int stride)
{
    mStride = stride;
}

void glh::VertexAttributePointer::setOffset(const unsigned int offset)
{
    mOffset = offset;
}

const GLenum glh::VertexAttributePointer::getGlType() const
{
    return mGlType;
}

const unsigned int& glh::VertexAttributePointer::getIndex() const
{
    return mIndex;
}

const bool& glh::VertexAttributePointer::getNormalized() const
{
    return mNormalized;
}

const unsigned int& glh::VertexAttributePointer::getOffset() const
{
    return mOffset;
}

const unsigned int& glh::VertexAttributePointer::getSize() const
{
    return mSize;
}

const unsigned int& glh::VertexAttributePointer::getStride() const
{
    return mStride;
}

void glh::VertexAttributePointer::enable()
{
    glEnableVertexAttribArray(mIndex);
    if(!created) {
        glVertexAttribPointer(mIndex, mSize, mGlType, mNormalized, mStride, reinterpret_cast<void*>(mOffset));
        created = true;
    }
}

void glh::VertexAttributePointer::disable()
{
    glDisableVertexAttribArray(mIndex);
}

bool glh::VertexAttributePointer::isAllowed(const std::vector<GLenum>& values, const GLenum value) {
    return std::binary_search(values.begin(), values.end(), value);
}

const std::vector<GLenum> glh::VertexAttributePointer::glTypes({ GL_BYTE,
          GL_UNSIGNED_BYTE,
          GL_SHORT,
          GL_UNSIGNED_SHORT,
          GL_INT,
          GL_UNSIGNED_INT,
          GL_FLOAT,
          GL_DOUBLE,
          GL_HALF_FLOAT,
          GL_FIXED
});

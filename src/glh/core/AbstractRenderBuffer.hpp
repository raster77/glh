#ifndef ABSTRACTRENDERBUFFER_HPP
#define ABSTRACTRENDERBUFFER_HPP

#include "GlObject.hpp" // Base class: glh::GlObject
#include "glad/glad.h"

namespace glh
{

class AbstractRenderBuffer : public glh::GlObject
{

public:
    AbstractRenderBuffer();
    AbstractRenderBuffer(const unsigned int width, const unsigned int height);
    AbstractRenderBuffer(const unsigned int width, const unsigned int height, const GLenum internatFormat);
    virtual ~AbstractRenderBuffer();

    void bind() final;
    void destroy() final;
    void unbind() final;

    const GLenum getInternalFormat() const;
    void setInternalFormat(const GLenum InternalFormat);

    const unsigned int getWidth() const;
    void setWidth(const unsigned int width);

    const unsigned int getHeight() const;
    void setHeight(const unsigned int height);

protected:
    GLenum mInternalFormat;
    unsigned int mWidth;
    unsigned int mHeight;

};

}

#endif // ABSTRACTRENDERBUFFER_HPP

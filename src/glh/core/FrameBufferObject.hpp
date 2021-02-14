#ifndef FRAMEBUFFEROBJECT_HPP
#define FRAMEBUFFEROBJECT_HPP

#include "GlObject.hpp" // Base class: glh::GlObject
#include "glh/core/AbstractTexture.hpp"
#include "glh/core/AbstractRenderBuffer.hpp"
#include <glad/glad.h>

namespace glh
{

class FrameBufferObject : public glh::GlObject
{
public:
    FrameBufferObject();
    ~FrameBufferObject();

    void bind() final;
    void create() final;
    void create(const unsigned int width, const unsigned height);
    void destroy() final;
    void unbind() final;

    void attachTexture2d(GLenum attachement, const glh::AbstractTexture& texture);
    void attachRenderBuffer(GLenum attachement, const glh::AbstractRenderBuffer& renderBuffer);

    const unsigned int getWidth() const;
    void setWidth(const unsigned int width);

    const unsigned int getHeight() const;
    void setHeight(const unsigned int height);

    bool isComplete();
    GLenum getStatus();

protected:
    unsigned int mWidth;
    unsigned int mHeight;
};

}

#endif // FRAMEBUFFEROBJECT_HPP
